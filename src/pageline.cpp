/*
    Copyright (C) 2011 Dmitriy Mityunin <mitunin.dmitry@gmail.com>

    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 2
    of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/
#include "pageline.h"
//#include "book.h"
#include <QtGui>
#include <QtCore>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QFile>
#include <QtGui/QFont>
#include "readerutils.h"
#include "math.h"
//
PageLine::PageLine()
{
	this->isStartParagraph = false;
	this->isEndParagraph = false;

        this->lastWord = 0;
        this->isPixmap = false;
}

TheWord::TheWord()
{
        this->x=0;
        this->w=0;
        this->data.clear();
}

QStringList PageLine::create( QStringList words, QString indent, QString f, float w, ReaderUtils &utils, hyphenator &hyph)
{
        int remainWords     = 0;
        this->f             = f;
        this->columnWidth   = w;
        int wordsSize       = 0;
        float lineSpacing;
        QFontMetrics *fm;
        this->data.clear();

        if( f == "title")
        {
            fm = new QFontMetrics( utils.titleFont );
            lineSpacing = utils.paragraphLineSpacing;
        }
        else if( f == "subtitle" )
        {
            fm = new QFontMetrics( utils.subtitleFont );
            lineSpacing = utils.paragraphLineSpacing;
        }
        else if( f == "cite" )
        {
            fm = new QFontMetrics( utils.citeFont );
            lineSpacing = utils.paragraphLineSpacing;
        }
        else if( f == "poem" )
        {
            fm = new QFontMetrics( utils.poemFont );
            lineSpacing = utils.paragraphLineSpacing;
        }
        else if( f.contains("footnote") )
        {
            fm = new QFontMetrics( utils.footnoteFont );
            lineSpacing = utils.footnoteLineSpacing;
        }
        else if( f == "indicator" )
        {
            fm = new QFontMetrics( utils.indicatorFont );
            lineSpacing = utils.paragraphLineSpacing;
        }
        else if( f == "epigraph" )
        {
            fm = new QFontMetrics( utils.epigraphFont );
            lineSpacing = utils.paragraphLineSpacing;
        }
        else
        {
            fm = new QFontMetrics( utils.paragraphFont );
            lineSpacing = utils.paragraphLineSpacing;
        }

	if( indent.length() > 0 )
	{
		this->words.append(indent);
                this->isStartParagraph = true;
                wordsSize += fm->width( indent );
	}
	
	int wordWidth = 0;

	foreach( QString word, words )
        {
               if( f == "title" && utils.isTitleInUpperCase )
                   word = word.toUpper();
               int wordWidth = utils.getWordWidth(word, f);
               if( wordWidth == -1 )
               {
                    wordWidth = fm->width(word+" ");
                    utils.setWordWidth(word, wordWidth, f);
                }

		if( wordsSize + wordWidth <= w || wordWidth > w)
                {
			wordsSize += wordWidth;
			this->words.append(word);

                        TheWord w;
                        w.data = word;
                        w.w = wordWidth;
                        this->data.append(w);

                        this->lastWord++;
			words.removeFirst();
			continue;
		}
                else
                {
                    QStringList hyphedWord;
                    if( utils.hyphsIsOn )
                        hyphedWord = hyph.hyphenateWord(word);
                    else
                        hyphedWord = QStringList(word);

                    if(!hyphedWord.isEmpty())
                    {
                        for(int i=hyphedWord.size()-1;i>=0;i--)
                        {
                            wordWidth = fm->width(hyphedWord[i]+"-");
                            if(wordsSize+wordWidth <= w || wordWidth > w)
                            {
                                wordsSize += wordWidth;
                                this->words.append(hyphedWord[i]+"-");

                                TheWord w;
                                w.data = hyphedWord[i]+"-";
                                w.w = wordWidth;
                                this->data.append(w);

                                this->lastWord++;
                                QString wordPart = word.right(word.size()-hyphedWord[i].size());
                                words.removeFirst();

                                words.insert(0,wordPart);
//                                words.prepend(word.mid[ hyphedWord[i].size()-1, word.size()-hyphedWord[i].size() ]);
                                break;
                            }
                        }
//                        continue;
                    }
                }

		break;
	}
	
	if( words.length() == 0 )
        {
            this->isEndParagraph = true;
//            this->lineHeight = fm->height() * utils.paragraphLineSpacing;
            this->lineHeight = fm->height() * lineSpacing;
//            this->lineHeight = fm->height();
        }
        else
        {
            this->isEndParagraph = false;
//            this->lineHeight = fm->height();
            this->lineHeight = fm->height() * lineSpacing;
//            this->lineHeight = fm->height() * utils.paragraphLineSpacing;
        }
	this->width = wordsSize;
	return words;
}

QString PageLine::justify(int w, ReaderUtils utils)
{
	//QStringList titleTags << "title" << "subtitle";
	QString line;
        QFontMetrics *fm;
        QString alignTo;
		
//	QFont paragraphFont;
//	paragraphFont.setPointSize(12);
//	paragraphFont.setFamily("Droid Sans");
	
        if( this->f == "title")
        {
            fm = new QFontMetrics( utils.titleFont );
            alignTo = "center";
        }
        else if( this->f == "subtitle" )
        {
            fm = new QFontMetrics( utils.subtitleFont );
            alignTo = "center";
        }
        else if( this->f == "cite" )
        {
            fm = new QFontMetrics( utils.citeFont );
            alignTo = "justify";
        }
        else if( this->f == "poem" )
        {
            fm = new QFontMetrics( utils.poemFont );
            alignTo = "left";
        }
        else if( this->f.contains("footnote") )
        {
            fm = new QFontMetrics( utils.footnoteFont );
            alignTo = "justify";
        }
        else if( this->f == "indicator" )
        {
            fm = new QFontMetrics( utils.indicatorFont );
            alignTo = "justify";
        }
        else if( this->f == "epigraph" )
        {
            fm = new QFontMetrics( utils.epigraphFont );
//            alignTo = "right";
            alignTo = "justify-right";
        }
        else if( this->isPixmap )
        {
            return " ";
        }
        else
        {
            fm = new QFontMetrics( utils.paragraphFont );
            alignTo = "justify";
        }

//        if( this->isEndParagraph && alignTo != "right" )
//                return this->words.join(" ");
//        if( this->isEndParagraph && this->f == "p" )
        if( this->isEndParagraph && this->f != "title" )
            alignTo = "left";
//        QFontMetrics *fm = new QFontMetrics( utils.paragraphFont );

        int sepSize = fm->width( QChar( 0x200a ) );
	int sepCount = 0;
	int sepInWords = 0;
        float spaceCharSize = fm->width( " " );
	QString sep = QChar( 0x200a );
        int wordsNum = this->words.length() - 1;
        if( this->words.at(0).at(0) == QString(" ").at(0) )
        {
            wordsNum -= 1;
        }
	
	if( wordsNum <= 0 ) wordsNum = 1;
	
	QString bS;
	
	sepCount = int(( w - this->width ) / sepSize);
        sepInWords = int( sepCount / wordsNum );
	
	for(int i=0;i<sepInWords;i++)
	{
		bS.append( QChar( 0x200a ) );
	}
	
	bS.append(" ");
	
	if( bS.length() <= 0 ) bS = QChar( 0x200a );
	
	//line = this->words.join(bS);
	int i = 0;
        if( alignTo == "justify" )
        {
            QString prevWord = "";
            foreach(QString word, this->words)
            {
                    QString s;
                    if( i < sepCount - sepInWords*wordsNum )
                    {
                            s.append( (QChar( 0x200a )) );
                    }
                    else
                    {
                            s = "";
                    }
//                    if( i == 0 )
                    if( i == 0 || prevWord.at(0) == QString(" ").at(0) )
//                    if( i == 0 && word.at(0) == QString(" ").at(0) )
                    {
                            line.append(word);
                    }
                    else
                    {
                            line.append(bS+s+word);
//                            line.append(word+bS+s);
                    }
                    i++;
                    prevWord = word;
            }

            float wordsWidth = this->data[0].w;
            if( this->isStartParagraph )
            {
                wordsWidth += spaceCharSize*utils.indentValue;
                this->data[0].x = spaceCharSize*utils.indentValue;
            }
            float wordsSeparatorWidth = (float(w)-this->width)/(this->data.length()-1);
//            qDebug()<<wordsSeparatorWidth;
            for(int wordsIt = 1; wordsIt < this->data.length(); wordsIt++)
            {
                this->data[wordsIt].x = wordsWidth+wordsSeparatorWidth;
                wordsWidth += wordsSeparatorWidth+this->data[wordsIt].w;
            }
        }
        else if( alignTo == "right" )
        {
            QString sepString = "";
            for(int sepNum=0;sepNum<sepCount;sepNum++)
            {
                sepString += (QChar( 0x200a ));
            }
            line = sepString + this->words.join(" ");


            float wordsWidth = this->data[0].w;
            float wordsSeparatorWidth = float(w)-this->width;
//            qDebug()<<wordsSeparatorWidth;
            this->data[0].x = wordsSeparatorWidth;
            wordsWidth += this->data[0].x;
            for(int wordsIt = 1; wordsIt < this->data.length(); wordsIt++)
            {
                this->data[wordsIt].x = wordsWidth;//+wordsSeparatorWidth;
                wordsWidth += this->data[wordsIt].w;
            }
        }
        else if( alignTo == "center" )
        {
            QString sepString = "";
            int sepLeftNum = int(sepCount / 2);
            int sepRightNum = sepCount - sepLeftNum;
            for(int sepNum=0;sepNum<sepLeftNum;sepNum++)
            {
                sepString += (QChar( 0x200a ));
            }
            line = sepString + this->words.join(" ");
            for(int sepNum=0;sepNum<sepRightNum;sepNum++)
            {
                sepString += (QChar( 0x200a ));
            }
            line += sepString;//                        if( this->fictionbook.bookFormats[i][0] == "empty-line" && this->utils.moveBigImages )
            //                        {
            ////                            if( paragraphPosition > 0 && paragraphPosition < this->bookParagraphs.count()-1 )
            //                            if( i > 0 && i < this->bookParagraphs.count()-1 )
            //                            {
            ////                                if( this->fictionbook.bookFormats[paragraphPosition-1][0] == "image" || this->fictionbook.bookFormats[paragraphPosition+1][0] == "image" )
            //                                if( this->fictionbook.bookFormats[i-1][0] == "image" || this->fictionbook.bookFormats[i+1][0] == "image" )
            //                                {
            //                                    break;
            //                                }
            //                            }
            //                        }
            float wordsWidth = this->data[0].w;
            float wordsSeparatorWidth = (float(w)-this->width)/2;
//            qDebug()<<wordsSeparatorWidth;
            this->data[0].x = wordsSeparatorWidth;
            wordsWidth += this->data[0].x;
            for(int wordsIt = 1; wordsIt < this->data.length(); wordsIt++)
            {
                this->data[wordsIt].x = wordsWidth;//+wordsSeparatorWidth;
                wordsWidth += this->data[wordsIt].w;
            }
        }
        else if( alignTo == "left" )
        {
            QString line;
            int i = 0;
            QString prevWord = "";
            foreach(QString word, this->words)
            {
                if( i == 0 || prevWord.at(0) == QString(" ").at(0) )
                {
                    line.append(word);
                }
                else
                {
                    line.append(QString(" "));
                    line.append(word);
                }
                i++;
                prevWord = word;
            }

            float wordsWidth = this->data[0].w;
//            float wordsSeparatorWidth = (float(w)-this->width)/(this->data.length()-1);
//            qDebug()<<wordsSeparatorWidth;
            for(int wordsIt = 1; wordsIt < this->data.length(); wordsIt++)
            {
                this->data[wordsIt].x = wordsWidth;//+wordsSeparatorWidth;
                wordsWidth += this->data[wordsIt].w;
            }

            return line;
//            return this->words.join(" ");
        }
        if( alignTo == "justify-right" )
        {
            foreach(QString word, this->words)
            {//                        if( this->fictionbook.bookFormats[i][0] == "empty-line" && this->utils.moveBigImages )
                //                        {
                ////                            if( paragraphPosition > 0 && paragraphPosition < this->bookParagraphs.count()-1 )
                //                            if( i > 0 && i < this->bookParagraphs.count()-1 )
                //                            {
                ////                                if( this->fictionbook.bookFormats[paragraphPosition-1][0] == "image" || this->fictionbook.bookFormats[paragraphPosition+1][0] == "image" )
                //                                if( this->fictionbook.bookFormats[i-1][0] == "image" || this->fictionbook.bookFormats[i+1][0] == "image" )
                //                                {
                //                                    break;
                //                                }
                //                            }
                //                        }
                    QString s;
                    if( i < sepCount - sepInWords*wordsNum )
                    {
                            s.append( (QChar( 0x200a )) );
                    }
                    else
                    {
                            s = "";
                    }
                    if( i == 0 )
                    {
                            line.append(word);
                    }
                    else
                    {
                            line.append(bS+s+word);
                    }
                    i++;
            }
        }
	
	//qDebug() << "Sep size:" << sepSize << " Sep count:" << sepCount << " Sep in words:" << sepInWords << " Words num:" << this->words.length();
	return line;
}

void PageLine::setPixmap(QString id, QByteArray data, int paragraphFontHeight, int w, int h)
{
    int lineHeight;
    this->pixmap.loadFromData(data);
    int pixmapHeight = this->pixmap.height();
    int pixmapWidth = this->pixmap.width();
    float aspect = float(this->pixmap.width()) / this->pixmap.height();
    int dx = this->pixmap.width() - w;
    if( this->pixmap.height() > h )
    {
        pixmapHeight = h;
        pixmapWidth = h * aspect;
        dx = pixmapWidth - w;
        w = pixmapWidth;
    }

    if( dx > 0 )
    {
        pixmapHeight = w / aspect;
        pixmapWidth = w;
    }
    lineHeight = paragraphFontHeight * ceil(float(pixmapHeight) / paragraphFontHeight);
    this->pixmapId      = id;
//    this->lineHeight    = this->pixmap.height();
    this->lineHeight    = lineHeight;
//    this->width         = this->pixmap.width();
    this->width         = pixmapWidth;
    this->height        = pixmapHeight;
    this->isPixmap      = true;
//    qDebug() << QString::number(pixmap.height());
}

bool PageLine::haveFootnotes()
{
//    qDebug()<<this->f;
    if(!this->footnotesId.isEmpty())
        return true;
    else
        return false;
}

//
