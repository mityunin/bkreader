#include "book.h"
#include "pageline.h"
#include "readerutils.h"
#include "hyphenator.h"
#include <iostream>
#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>
#include <QtXml/QDomNode>
#include <QtGui>
#include <QtCore>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QList>
#include <QtCore/QFile>
#include <QtCore/QDir>
#include <QtGui/QFont>
#include <QtGui/QFontMetrics>
#include <QtCore/QTime>
#include <QTextStream>
//#include "quazip/quazip.h"
//#include "quazip/quazipfile.h"
#include "osdab-zip/unzip.h"
//
book::book(  ) 
{
    this->bookFileName  = "";
    this->columnsGap    = 20;

    this->currentPage   = 0;
    this->currentWord   = 0;

    for( int i=0; i<this->utils.indentValue; i++ )
        this->indent += " ";

    if(this->loadBookPosition())
        this->loadBook(this->bookFileName);
}

void book::loadBook(QString filename)
{
    this->bookParagraphs.clear();
    this->lines.clear();
    this->pages.clear();

    this->currentWord = this->getBookPositionInHistory(filename);

    if( filename.right(3) == "zip" )
    {
        UnZip unzip;
        UnZip::ErrorCode ec = unzip.openArchive(filename);

        if( ec != UnZip::Ok )
            return;

        QStringList filesInArchive = unzip.fileList();

        if( filesInArchive.count() > 0 )
        {
            if( filesInArchive.at(0).contains(QString(".fb2")) || filesInArchive.at(0).contains(QString(".txt")))
            {
                filename = filesInArchive.at(0);
                ec = unzip.extractFile(filename, QDir::tempPath());
                if( ec == UnZip::Ok )
                {
                    filename = QDir::tempPath()+QString("/")+filename;
                    unzip.closeArchive();
                }
            }
        }
    }

    if( filename.right(3) == "txt" )
        this->loadTextBook(filename);
    else
    {
        this->fictionbook.loadFB2(filename);
        this->bookParagraphs = this->fictionbook.bookParagraphs;
    }

    if( !this->fictionbook.authorFirstName.isEmpty() )
        this->authorFirstName = this->fictionbook.authorFirstName;

    if( !this->fictionbook.authorMiddleName.isEmpty() )
        this->authorMiddleName = this->fictionbook.authorMiddleName;

    if( !this->fictionbook.authorLastName.isEmpty() )
        this->authorLastName = this->fictionbook.authorLastName;

    if( !this->fictionbook.bookTitle.isEmpty() )
        this->bookTitle = this->fictionbook.bookTitle;

    this->processBook();
    if( filename.startsWith(QDir::tempPath()) )
        QFile::remove(filename);
}

void book::processBook()
{
    if( this->bookParagraphs.length() <= 0 ) return;
    this->breakLines();
    this->makePages();
}

void book::breakLines()
{
    QTime timer;
    timer.start();
    this->lines.clear();
    this->footnotes.clear();

    //create hyphenator object
    hyphenator hyph;
    hyph.loadHyphPatterns(QString("ru"));

    //i - iterator for bookFormats list
    int i=0;

    //iterate paragraphs
    foreach(QStringList p, this->bookParagraphs)
    {
        //width - book page width
        int width = this->getColumnWidth();

        if( this->fictionbook.bookFormats.count() > 0 )
        {
            if( this->fictionbook.bookFormats[i][0] == "image" )
            {
                PageLine imageLine;
                QFontMetrics *fm = new QFontMetrics(this->utils.paragraphFont);
                imageLine.setPixmap(p[0], this->fictionbook.binarys[p[0]], fm->height()*this->utils.paragraphLineSpacing, this->getColumnWidth(), this->getColumnHeight());
                this->lines.append(imageLine);
                i++;
                continue;
            }
            else if( this->fictionbook.bookFormats[i][0] == "cite" )
            {
                width = width - this->utils.citeMargin*2;
            }
            else if( this->fictionbook.bookFormats[i][0] == "poem" )
            {
                width = width - this->utils.poemMargin*2;
            }
            else if( this->fictionbook.bookFormats[i][0] == "epigraph" )
            {
                width = width - this->utils.epigraphMargin;
            }
            //                    else if( this->fictionbook.bookFormats[i][0] == "empty-line" )
            //                    {
            //                        if( paragraphPosition > 0 && paragraphPosition < this->bookParagraphs.count()-1 )
            //                        {
            //                            if( this->fictionbook.bookFormats[paragraphPosition-1][0] == "image" || this->fictionbook.bookFormats[paragraphPosition+1][0] == "image" )
            //                            {
            //                                int tttt = 0;
            //                                continue;
            //                            }
            //                        }
            //                    }
        }

        QString indent = this->indent;
        //no indent for titles and subtitles
        //!!!add indent option to settings
        if( this->fictionbook.bookFormats[i][0] == "title" )
            indent = "";
        if( this->fictionbook.bookFormats[i][0] == "subtitle" )
            indent = "";

        //split paragraph to single words
        QStringList words;
        for(int j=0; j<p.length(); j++)
            words += p[j].split(" ");

        int startLineWord = 0;
        int endLineWord = 0;

        //iterate throu paragraph words list while its not empty
        while( words.length() > 0 )
        {
            startLineWord = endLineWord;
            //if paragraph is "empty-line" and next or previous line is "image"
            //then break and go to next paragraph
            if( this->fictionbook.bookFormats[i][0] == "empty-line" && this->utils.moveBigImages )
            {
                if( i > 0 && i < this->bookParagraphs.count()-1 )
                {
                    if( this->fictionbook.bookFormats[i-1][0] == "image" || this->fictionbook.bookFormats[i+1][0] == "image" )
                    {
                        break;
                    }
                }
            }

            PageLine line;
            //create line from words, exclude used words from words list
            words = line.create(words, indent, this->fictionbook.bookFormats[i][0], width, this->utils, hyph);
            endLineWord += line.words.size();
            if( i < this->fictionbook.bookFormats.count()-1 )
            {
                //for titles make big line height
                //!!!add line height option to settings
                if( this->fictionbook.bookFormats[i][0] == "title" && this->fictionbook.bookFormats[i+1][0] != "title" )
                {
                    line.lineHeight = line.lineHeight*this->utils.titleBottomMargin;
                }
            }
            //???
            if( this->fictionbook.bookFormats.count() > 0 )
            {
                //???
                line.f = this->fictionbook.bookFormats[i][0];
                QStringList paragraphFormats = this->fictionbook.bookFormats[i];
                //if line have footnotes
                //then add footnotes ID to line
                foreach( QString tmpFootnoteId, paragraphFormats )
                {
//                    QString footnoteId = this->fictionbook.bookFormats[i][1];
//                    foreach( QString tmpFootnoteId, this->fictionbook.bookFormats[i] )
//                    {
                    if( tmpFootnoteId.contains("footnote:") )
                    {
                        QString footnoteId = tmpFootnoteId.replace("footnote:","");
                        if( this->fictionbook.footnotesRange[footnoteId][0]>=startLineWord && this->fictionbook.footnotesRange[footnoteId][1]<=endLineWord )
                        {
                            line.footnotesId.append(footnoteId);
                        }
                    }
                }
            }


            //add line to lines list
            this->lines.append(line);
            indent = "";
        }

        i++;
    }

    //break footnotes
    i=0;
    int width = this->getColumnWidth();

    QHash<QString, QHash<QString, QStringList> >::iterator end = this->fictionbook.footnotes.end();
    for(QHash<QString, QHash<QString, QStringList> >::iterator iter=this->fictionbook.footnotes.begin(); iter!=end;++iter)
    {
        QString indent = this->indent;

        QHash<QString, QStringList> footnote = iter.value();
        QHash<QString, QStringList>::iterator endParagraph = footnote.end();
        QHash<QString, QStringList> fn = iter.value();
        QStringList words;
        QStringList p;
        p.append(QStringList(fn["title"])+QStringList(")"));
        p.append(fn["p"]);

        for(int j=0; j<p.length(); j++)
            words += p[j].split(" ");

        while( words.length() > 0 )
        {
            PageLine line;
            words = line.create(words, "", "footnote", width, this->utils, hyph);
            line.f = "footnote";
            this->footnotes[ iter.key() ].append(line);
            indent = "";
        }
        i++;
    }
}

int book::getPageHeight()
{
    return this->pageHeight;
}

void book::setPageHeight(int h)
{
    this->pageHeight = h;
}

void book::makePages()
{
    float rowsHeightLeft = this->getColumnHeight();
    this->pages.clear();
    QList<PageLine> page;
    QList<PageLine> restFootnotesLines;
    QList<PageLine> restPixmaps;
    long currentPage = 0;
    long currentWord = 0;
    long prevWord    = 0;
    float restFootnotesHeight = 0;
    QString prevLineFormat;

    if( !this->fictionbook.coverPageId.isNull() )
    {
        PageLine coverline;
        QFontMetrics *fm = new QFontMetrics(this->utils.paragraphFont);
        coverline.setPixmap(this->fictionbook.coverPageId, this->fictionbook.binarys[ this->fictionbook.coverPageId ], fm->height()*this->utils.paragraphLineSpacing, this->getColumnWidth(), this->getColumnHeight());
        page.append(coverline);
        rowsHeightLeft = 0;
    }

    PageLine currentTitle;

    foreach(PageLine line, this->lines)
    {
        currentWord += line.lastWord;
        if( currentWord >= this->currentWord && prevWord <= this->currentWord )
        {
            this->currentPage = currentPage;
        }

        prevWord += line.lastWord;

        if(line.haveFootnotes())
        {
//            QStringList fooid = line.footnotesId;
            restFootnotesLines.append(this->getFootnotesLines(line.footnotesId));
        }
        restFootnotesHeight = this->getPageLinesHeight(restFootnotesLines);

        if( line.isPixmap && rowsHeightLeft-restFootnotesHeight-line.lineHeight < 0 )
        {
            restPixmaps.append(line);
            continue;
        }

        while( !restPixmaps.isEmpty() )
        {
            PageLine pixmap = restPixmaps.takeFirst();

            if( rowsHeightLeft-restFootnotesHeight-pixmap.lineHeight >= 0 )
            {
                page.append(pixmap);
                rowsHeightLeft -= pixmap.lineHeight;
                prevLineFormat = pixmap.f;
            }
            else
            {
                if( rowsHeightLeft-restFootnotesHeight-line.lineHeight <= 0 && pixmap.lineHeight >= this->getColumnHeight() )
                {
                    this->pages.append(page);
                    currentPage++;
                    page.clear();
                    page.append(pixmap);
                    rowsHeightLeft  = this->getColumnHeight();
                    prevLineFormat = pixmap.f;
                    this->pages.append(page);
                    currentPage++;
                    page.clear();
                    continue;
                }
                restPixmaps.prepend(pixmap);
                break;
            }
        }

        if( rowsHeightLeft-restFootnotesHeight-line.lineHeight >= 0)
        {
            if( line.f == "title" && prevLineFormat != QLatin1String("title") )
            {
                pages.append(page);
                page.clear();
                currentPage++;
                rowsHeightLeft = this->getColumnHeight();
            }
            page.append(line);
            rowsHeightLeft -= line.lineHeight;
            prevLineFormat = line.f;
        }
        else
        {
            //                for(int i=0;i<restFootnotesLines.size();i++)
            //                firstFootnoteLineHeight = 0;
            while(!restFootnotesLines.empty())
            {
                PageLine pl = restFootnotesLines.takeFirst();
                if( rowsHeightLeft-pl.lineHeight >= 0 )
                {
                    page.append(pl);
                    rowsHeightLeft -= pl.lineHeight;
                    prevLineFormat = line.f;
                }
                else
                {
                    restFootnotesLines.prepend(pl);
                    break;
                }
            }

            this->pages.append(page);
            currentPage++;
            page.clear();
            page.append(line);
            prevLineFormat = line.f;
            rowsHeightLeft  = float(this->getColumnHeight())-line.lineHeight;
        }
    }
    this->pages.append(page);
}

void book::setPageWidth(int w)
{
    this->pageWidth = w;
}

int book::getPageWidth()
{
    return this->pageWidth;
}

float book::getColumnWidth()
{
    switch( this->utils.rotateValue )
    {
    case 0:
        this->columnWidth = int(this->getPageWidth()/this->utils.columnsNum) - this->utils.leftMargin - this->utils.rightMargin;
        break;
    case 1:
        this->columnWidth = int(this->getPageHeight()/this->utils.columnsNum) - this->utils.topMargin - this->utils.bottomMargin;
        break;
    case 2:
        this->columnWidth = int(this->getPageHeight()/this->utils.columnsNum) - this->utils.topMargin - this->utils.bottomMargin;
        break;
    }
    return this->columnWidth;
}

float book::getColumnHeight()
{
    switch( this->utils.rotateValue )
    {
    case 0:
        this->columnHeight = float(this->getPageHeight()) - this->utils.topMargin - this->utils.bottomMargin;
        break;
    case 1:
        this->columnHeight = float(this->getPageWidth()) - this->utils.leftMargin - this->utils.rightMargin;
        break;
    case 2:
        this->columnHeight = float(this->getPageWidth()) - this->utils.leftMargin - this->utils.rightMargin;
        break;
    }
    return this->columnHeight;
}

void book::setFontBigger(int s)
{
    if( this->utils.paragraphFont.pointSize() >= 25 ) return;
    this->utils.paragraphFont.setPointSize(this->utils.paragraphFont.pointSize()+s);
    this->utils.titleFont.setPointSize(this->utils.titleFont.pointSize()+s);
    this->utils.subtitleFont.setPointSize(this->utils.subtitleFont.pointSize()+s);
    this->utils.poemFont.setPointSize(this->utils.poemFont.pointSize()+s);
    this->utils.citeFont.setPointSize(this->utils.citeFont.pointSize()+s);
    this->utils.footnoteFont.setPointSize(this->utils.footnoteFont.pointSize()+s);
    this->utils.indicatorFont.setPointSize(this->utils.indicatorFont.pointSize()+s);
    this->utils.epigraphFont.setPointSize(this->utils.epigraphFont.pointSize()+s);
    this->utils.wordsWidths.clear();
    this->processBook();
    this->utils.writeSettings();
}

void book::setFontSmaller(int s)
{
    if( this->utils.paragraphFont.pointSize() <= 5 ) return;
    this->utils.paragraphFont.setPointSize(this->utils.paragraphFont.pointSize()-s);
    this->utils.titleFont.setPointSize(this->utils.titleFont.pointSize()-s);
    this->utils.subtitleFont.setPointSize(this->utils.subtitleFont.pointSize()-s);
    this->utils.poemFont.setPointSize(this->utils.poemFont.pointSize()-s);
    this->utils.citeFont.setPointSize(this->utils.citeFont.pointSize()-s);
    this->utils.footnoteFont.setPointSize(this->utils.footnoteFont.pointSize()-s);
    this->utils.indicatorFont.setPointSize(this->utils.indicatorFont.pointSize()-s);
    this->utils.epigraphFont.setPointSize(this->utils.epigraphFont.pointSize()-s);
    this->utils.wordsWidths.clear();
    this->processBook();
    this->utils.writeSettings();
}

void book::setLinesBigger()
{
    this->utils.paragraphLineSpacing += 0.1;
    this->processBook();
    this->utils.writeSettings();
}

void book::setLinesSmaller()
{
    this->utils.paragraphLineSpacing -= 0.1;
    this->processBook();
    this->utils.writeSettings();
}

long book::setCurrentWord()
{
    this->currentWord = 0;
    if( this->currentPage <= 0 ) return 0;

    for( int i=0; i<=this->currentPage; i++ )
    {
        foreach( PageLine l, this->pages[i])
        {
            this->currentWord += l.lastWord;
        }
    }

    return this->currentPage;
}

void book::loadTextBook(QString filename)
{
    this->bookParagraphs.clear();
    QFile f(filename);
    if(!f.open(QIODevice::ReadOnly))
        return;

    QTextStream in(&f);
    //    in.
    in.setCodec("UTF-8");

    while( !in.atEnd() )
    {
        QString line = in.readLine();
        this->bookParagraphs.append( QStringList( line ) );
    }
    f.close();
}

void book::saveBookPosition()
{
    if( !this->bookFileName.isEmpty() && this->currentWord )
    {
        QSettings settings("MyReader", "recent");

        QString recentBook;
        recentBook.append("recent/");
        recentBook.append(this->bookFileName);
        settings.setValue( recentBook, QVariant(qlonglong(this->currentWord)).toString() );
        settings.setValue( "lastread/filename", this->bookFileName );
        settings.setValue( "lastread/position", QVariant(qlonglong(this->currentWord)).toString() );
    }
}

bool book::loadBookPosition()
{
    bool result;

    QSettings settings("MyReader", "recent");

    QString fileName;
    int position = 0;
    fileName = settings.value( "lastread/filename" ).toString();
    position = settings.value( "lastread/position" ).toInt();
    if( !fileName.isEmpty() && position >= 0 )
    {
        this->bookFileName = fileName;
        this->currentWord = position;
        result = true;
    }
    else
    {
        result = false;
    }

    return result;
}

int book::getBookPositionInHistory(QString filename)
{
    QSettings settings("MyReader", "recent");

    int position = 0;
    position = settings.value( QString("recent/")+filename, 0 ).toInt();

    return position;
}

int book::getFootnotesHeight(QStringList footnotesId)
{
    float h=0;
    foreach(QString footnoteId, footnotesId)
    {
        QList<PageLine> pllist = this->footnotes[footnoteId];

        foreach(PageLine pl, pllist)
        {
            h += float(pl.lineHeight);
        }
    }

    return ceil(h);
}

QList<PageLine> book::getFootnotesLines(QStringList footnotesId)
{
    QList<PageLine> lines;
    foreach( QString footnoteId, footnotesId )
    {
        QList<PageLine> pllist = this->footnotes[ footnoteId ];
        foreach(PageLine pl, pllist)
        {
            lines.append(pl);
        }
    }

    return lines;
}

float book::getPageLinesHeight(QList<PageLine> pllist)
{
    float h = 0;
    foreach(PageLine pl, pllist)
    {
        h += float(pl.lineHeight);
    }
    return h;
}

QTextLayout::FormatRange book::getFormatRange(QString f, int start, int length)
{
    QTextCharFormat charFormat;
    QTextLayout::FormatRange formatRange;

    formatRange.start = start;
    formatRange.length = length;

    if( f == "title" )
    {
        charFormat.setFont( this->utils.titleFont );
    }
    else if( f == "subtitle" )
    {
        charFormat.setFont( this->utils.subtitleFont );
    }
    else if( f == "poem" )
    {
        charFormat.setFont( this->utils.poemFont );
    }
    else if( f == "cite" )
    {
        charFormat.setFont( this->utils.citeFont );
    }
    else if( f == "footnote" )
    {
        charFormat.setFont( this->utils.footnoteFont );
    }
    else if( f == "epigraph" )
    {
        charFormat.setFont( this->utils.epigraphFont );
    }
    else
    {
        charFormat.setFont( this->utils.paragraphFont );
    }

    formatRange.format = charFormat;
    return formatRange;
}

float book::getColumnLeftCoord(int i)
{
    float x = this->utils.leftMargin*i + this->getColumnWidth()*i + this->utils.rightMargin*i;
    return x;
}

float book::getColumnRightCoord(int i)
{
    float x = this->utils.leftMargin*(i+1) + this->getColumnWidth()*(i+1) + this->utils.rightMargin*(i+1);
    return x;
}

//
