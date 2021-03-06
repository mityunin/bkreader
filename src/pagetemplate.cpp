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
#include "pagetemplate.h"
#include "pageline.h"
#include "readerutils.h"
//#include <iostream>
#include <QPainter>
#include <QtGui/QTextLayout>
#include <QtGui/QTextLine>
#include <QtGui/QKeyEvent>
#include <QtGui/QFileDialog>
#include <QtGui/QFontDialog>
#include <QtCore/QTime>
#include <QtGui/QShortcut>
//#include <QtGui/QBrush>
#include <QTimer>
#include <qmath.h>
//
PageTemplate::PageTemplate( QWidget *parent ):QWidget(parent)
{
        this->setFocusPolicy( Qt::StrongFocus );
	
	QShortcut *shortOpenBook = new QShortcut(QKeySequence(tr("Ctrl+O", "File|Open")), this);
	QShortcut *shortFontBigger = new QShortcut(QKeySequence(tr("Alt+Right", "View|Font Bigger")), this);
	QShortcut *shortFontSmaller = new QShortcut(QKeySequence(tr("Alt+Left", "View|Font Smaller")), this);
	QShortcut *shortLinesBigger = new QShortcut(QKeySequence(tr("Alt+Down", "View|Line Space Bigger")), this);
	QShortcut *shortLinesSmaller = new QShortcut(QKeySequence(tr("Alt+Up", "View|Line Space Smaller")), this);
        QShortcut *shortHideMenu = new QShortcut(QKeySequence(tr("Ctrl+M", "View|Hide Menu")), this);

	connect(shortOpenBook, SIGNAL( activated() ), this, SLOT( openFile() ) );
	connect(shortFontBigger, SIGNAL( activated() ), this, SLOT( setFontBigger() ) );
	connect(shortFontSmaller, SIGNAL( activated() ), this, SLOT( setFontSmaller() ) );
	connect(shortLinesBigger, SIGNAL( activated() ), this, SLOT( setLinesBigger() ) );
	connect(shortLinesSmaller, SIGNAL( activated() ), this, SLOT( setLinesSmaller() ) );
        connect(shortHideMenu, SIGNAL( activated() ), this, SLOT( setHideMenu() ) );

        QTimer *timer = new QTimer();
        connect(timer, SIGNAL( timeout() ), this, SLOT( showTime() ));
        timer->start(1000);
}

void PageTemplate::paintEvent(QPaintEvent *event)
{
//        QPixmap widgetPixmap;
//        QPainter painter(&this->widgetPixmap);
        QPainter painter(this);
//        painter.setRenderHints(QPainter::TextAntialiasing, true);

        painter.save();
        QPen pen;
//        pen.setColor(QColor("#202020"));
        pen.setColor(QColor(this->b->utils.paracolor));
        painter.setPen(pen);
        switch( this->b->utils.rotateValue )
        {
        case 1:
            painter.translate( 0, this->b->getPageHeight() );
            painter.rotate( -90 );
            break;
        case 2:
            painter.translate( this->b->getPageWidth(), 0 );
            painter.rotate( 90 );
            break;
        }

        painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::HighQualityAntialiasing | QPainter::SmoothPixmapTransform, true);

        //draw book page picture
        QPixmap pageBg(this->b->getColumnWidth()-6, this->b->getColumnHeight()-6);
//        pageBg.fill(QColor(QColor(this->b->utils.bgcolor)).rgb());

//        QPixmap pagePattern("/home/sa/Downloads/brushed_alu.png");
//        pagePattern.

        QPixmap pagePattern(QDir::homePath()+"/.config/bkreader/pixmaps/"+this->b->utils.pixmapPatternFile);
        QPixmap pageThinLine(this->b->getColumnWidth(), 1);
        pageThinLine.fill(this->b->utils.paracolor);

        QLinearGradient gradBg(this->b->getColumnWidth()*0.5, 0, this->b->getColumnWidth()*0.5, this->b->getColumnHeight());
        gradBg.setColorAt(0, QColor(QColor( this->b->utils.bgColorFrom )).rgb());
        gradBg.setColorAt(1, QColor(QColor( this->b->utils.bgColorTo )).rgb());
        QPainter bgPixmapPainter(&pageBg);

//        QPixmap pageBgShadow(this->b->getColumnWidth()-6, this->b->getColumnHeight()-6);
//        pageBgShadow.fill(QColor(QColor("#C6C6C6")).rgb());

        QBrush pageBgBrush;
        pageBgBrush.setColor(QColor("#aaaaaa").rgb());
        painter.setBrush(pageBgBrush);

        pen.setCosmetic(true);
        pen.setWidthF(0.4);
        painter.setPen(pen);

        int pageBgIndent = 6;

        if(this->b->utils.bgType == "grad")
        {

            bgPixmapPainter.fillRect(0, 0, this->b->getPageWidth(true), this->b->getPageHeight(true),gradBg);
            painter.drawPixmap(0, 0, this->b->getPageWidth(true), this->b->getPageHeight(true),pageBg);
        }
        else
            painter.drawTiledPixmap(0,0,this->b->getPageWidth(true),this->b->getPageHeight(true), pagePattern);

        for(int i=0;i<this->b->utils.columnsNum;i++)
        {
            //draw indicator line
            int indicatorXFrom = this->b->utils.getLeftMargin(i)*(i+1) + this->b->getColumnWidth()*i + this->b->utils.getRightMargin(i)*i;
            int indicatorXTo = this->b->utils.getLeftMargin(i)*(i+1) + this->b->getColumnWidth()*(i+1) + this->b->utils.getRightMargin(i)*i;
//            painter.drawLine(indicatorXFrom, this->b->utils.indicatorFontHeight, indicatorXTo, this->b->utils.indicatorFontHeight);
            painter.drawPixmap(indicatorXFrom, this->b->utils.indicatorFontHeight, pageThinLine);
        }


        for(int i=0; i<this->b->utils.columnsNum;  i++)
        {
		if( this->b->pages.length() <= 0 ) break;
                if( this->b->pages.length() <= this->b->currentPage+i ) break;
                QList<PageLine> page = this->b->pages[ this->b->currentPage+i ];

                if( page.isEmpty() )
                {
                    PageLine emptyLine;
                    emptyLine.words.append(" ");
                    page.append(emptyLine);
                }
//                this->b->setCurrentWord();
	
//		this->drawLayout(page, i);
//		this->layout.draw(&painter, QPointF(0,0));

                int y = this->b->utils.topMargin;
                int w = 0;
                int h = 0;
                QString previousFormat = "";
//                int lineNum = 1;
                int lineY = this->b->utils.topMargin;
//                int lineX = this->b->
                foreach(PageLine l, page)
                {
                    int x = this->b->utils.getLeftMargin(i) + this->b->getColumnWidth()*i+this->b->utils.getRightMargin(i)*i;
                    float lineX = this->b->utils.getLeftMargin(i) + this->b->getColumnWidth()*i+this->b->utils.getRightMargin(i)*i;
                    lineY += l.lineHeight;

                    if( l.isPixmap )
                    {
//                        int dx = l.width - this->b->getColumnWidth();
//                        int dx = l.pixmap.width() - this->b->getColumnWidth();
                        int dx = l.width - this->b->getColumnWidth();
//                        int dy = l.lineHeight - this->b->getColumnHeight() - y;
//                        int dy = l.pixmap.height() - this->b->getColumnHeight() - y;
                        int dy = l.height - this->b->getColumnHeight() - y;
                        if( dx > 0 || dy > 0)
                        {
//                            float aspect = l.width / l.lineHeight;
//                            float aspect = float(l.pixmap.width()) / l.pixmap.height();
                            float aspect = float(l.width) / l.height;
                            if( dx >= dy )
                            {
                                w = this->b->getColumnWidth();
                                h = w / aspect;
                            }
                            else
                            {
                                h = this->b->getColumnHeight() - y;
                                w = h * aspect;
                            }
                        }
                        else
                        {
                            w = l.width;
//                            w = l.pixmap.width();
                            h = l.lineHeight;
//                            h = l.pixmap.height();
                        }
                        if( page.size() == 1 )
                            y = this->b->utils.topMargin + ( this->b->getColumnHeight() - h ) / 2;
                        int halfColumnWidth = ( this->b->getColumnWidth() - w ) / 2;
                        x = this->b->getColumnWidth() * i + this->b->utils.getRightMargin(i) * i + this->b->utils.getLeftMargin(i) * (i+1) + halfColumnWidth;
                        painter.drawPixmap( x, y, w, h, l.pixmap );

                    }
                    y += l.lineHeight;
                    if( l.f == "title" ) this->currentTitle = l.words.join(" ");

                    if( l.f == "footnote" && previousFormat != "footnote" )
                    {
                        float footnotesOnPageHeight = 0;
                        foreach( PageLine pl, page )
                        {
                            if( pl.f == "footnote" ) footnotesOnPageHeight += pl.lineHeight;
                        }

                        float footnoteSeparatorY = this->b->getColumnHeight()+this->b->utils.topMargin-footnotesOnPageHeight;
                        float footnoteSeparatorX = this->b->utils.getLeftMargin(i)*(i+1)+this->b->utils.getRightMargin(i)*i+this->b->getColumnWidth()*i;
                        previousFormat = "footnote";
                        painter.drawLine(footnoteSeparatorX, footnoteSeparatorY, footnoteSeparatorX+(this->b->getColumnWidth()/3), footnoteSeparatorY);
                    }


                    l.justify(this->b->getColumnWidth(), this->b->utils);
                    foreach(TheWord word, l.data)
                    {
//                        qDebug()<<word.x;
                        lineX = word.x + this->b->utils.getLeftMargin(i)*(i+1) + this->b->getColumnWidth()*i + this->b->utils.getRightMargin(i)*i;;//this->b->utils.getLeftMargin(i) + this->b->getColumnWidth()*i+this->b->utils.getRightMargin(i)*i;

                        if( l.f == "p" )
                            painter.setFont(this->b->utils.paragraphFont);
                        else if( l.f == "title" || l.f == "subtitle" )
                            painter.setFont(this->b->utils.titleFont);
                        else if( l.f == "footnote" )
                            painter.setFont(this->b->utils.footnoteFont);
                        else if( l.f == "cite" )
                            painter.setFont(this->b->utils.citeFont);
                        else if( l.f == "epigraph" )
                            painter.setFont(this->b->utils.epigraphFont);
                        else if( l.f == "poem" )
                            painter.setFont(this->b->utils.poemFont);

                        painter.drawText(lineX, lineY, word.data);
                    }
                }
	}

//        painter.drawText( this->b->utils.getLeftMargin(0), 0, this->b->getColumnWidth(), this->b->utils.topMargin, Qt::AlignVCenter, this->currentTitle );
        QString bookInfo;
        bookInfo.clear();

        if( !this->b->authorFirstName.isEmpty() )
            bookInfo = this->b->authorFirstName;

        if( !this->b->authorLastName.isEmpty() )
            bookInfo += QString(" ")+this->b->authorLastName+".";

        if( !this->b->bookTitle.isEmpty() )
            bookInfo += QString(" ")+this->b->bookTitle;

        bookInfo += ". "+this->b->getCurrentChapter();
        int currentPageNum = this->b->currentPage;
        int pagesLenNum = this->b->pages.length();

        currentPageNum = qRound(currentPageNum/this->b->utils.columnsNum);
        pagesLenNum = qRound(pagesLenNum/this->b->utils.columnsNum);

        painter.setFont(this->b->utils.indicatorFont);

//        painter.drawText( this->b->utils.getLeftMargin(0), 0, this->b->getColumnWidth(), this->b->utils.indicatorFontHeight, Qt::AlignVCenter, bookInfo.trimmed() );
        painter.drawText( this->b->utils.getLeftMargin(0), 0, this->b->getColumnWidth(), this->b->utils.indicatorFontHeight, Qt::AlignVCenter, bookInfo.trimmed() );

//        painter.drawText( this->b->utils.getLeftMargin(0), 0, this->b->getPageWidth(true)-this->b->utils.getLeftMargin(0)-this->b->utils.getRightMargin(this->b->utils.columnsNum-1), this->b->utils.indicatorFontHeight, Qt::AlignRight+Qt::AlignVCenter, QString::number(this->b->currentPage)+" / "+QString::number(this->b->pages.length()));
        painter.drawText( this->b->utils.getLeftMargin(0), 0, this->b->getPageWidth(true)-this->b->utils.getLeftMargin(0)-this->b->utils.getRightMargin(this->b->utils.columnsNum-1), this->b->utils.indicatorFontHeight, Qt::AlignRight+Qt::AlignVCenter, QString::number(currentPageNum)+" / "+QString::number(pagesLenNum));

//        painter.drawText(this->b->utils.getLeftMargin(0), this->b->utils.topMargin+this->b->getColumnHeight(), this->b->getColumnWidth(), this->b->utils.bottomMargin, Qt::AlignVCenter, QString::number(this->b->currentPage)+" / "+QString::number(this->b->pages.length()));

//        QTime *time = new QTime();
//        painter.drawText(this->b->utils.getLeftMargin(0),this->b->utils.topMargin+this->b->getColumnHeight(),this->b->getColumnWidth()*this->b->utils.columnsNum+this->b->utils.getLeftMargin(0)*(this->b->utils.columnsNum-1)+this->b->utils.getRightMargin(0)*(this->b->utils.columnsNum-1),this->b->utils.bottomMargin,Qt::AlignVCenter | Qt::AlignRight,time->currentTime().toString("hh:mm"));

        painter.restore();
        this->b->setCurrentWord();
}

void PageTemplate::drawLayout(QList<PageLine> page, int columnNum)
{
	QString text;
        QString endLine( QChar( 0x2028 ) );
        int lineStart = 0;
        int lineLength = 0;
        QList<QTextLayout::FormatRange> formatRangeList;

	foreach(PageLine line, page)
	{
                int width = this->b->getColumnWidth();
                if( line.f == "cite" )
                    width = width - this->b->utils.citeMargin*2;
                else if( line.f == "poem" )
                    width = width - this->b->utils.poemMargin*2;
                else if( line.f == "epigraph" )
                    width = width - this->b->utils.epigraphMargin;


                lineStart += lineLength;
                QString lineText = line.justify(width, this->b->utils);
                lineLength = lineText.size()+1; //line size + new line symbol

                formatRangeList.append(this->b->getFormatRange(line.f, lineStart, lineLength));
                text.append(lineText);
		text.append(endLine);
	}
	
        this->layout.setFont(this->b->utils.paragraphFont);
	this->layout.setText(text);
	
        int y = this->b->utils.topMargin;

        this->layout.setAdditionalFormats(formatRangeList);
	this->layout.beginLayout();
	QTextLine l = this->layout.createLine();
	int i = 0;
        QString previosFormat = "";
	while( l.isValid() )
	{
                PageLine pageLine = page[i];
                int x = this->b->utils.getLeftMargin(columnNum)*(columnNum+1) + columnNum * this->b->getColumnWidth() + columnNum * this->b->utils.getRightMargin(columnNum);
                if( pageLine.f == "cite" )
                    x += this->b->utils.citeMargin;
                else if( pageLine.f == "poem" )
                    x += this->b->utils.poemMargin;
                else if( pageLine.f == "epigraph" )
                    x += this->b->utils.epigraphMargin;
                else if( pageLine.f == "footnote" && previosFormat != "footnote" )
                {
                    float footnotesOnPageHeight = 0;
                    foreach( PageLine pl, page )
                    {
                        if( pl.f == "footnote" ) footnotesOnPageHeight += pl.lineHeight;
                    }

                    y = this->b->getColumnHeight()+this->b->utils.topMargin-footnotesOnPageHeight;
                    previosFormat = "footnote";
                }

		l.setPosition(QPointF(x,y));
                y += pageLine.lineHeight;
                if( i < page.length()-1 ) i++;
		l = this->layout.createLine();
	}
        this->layout.endLayout();
}

void PageTemplate::setBook(book *b)
{
	this->b = b;
}

void PageTemplate::resizeEvent(QResizeEvent *event)
{
	this->b->setPageWidth( this->geometry().width() );
	this->b->setPageHeight( this->geometry().height() );
	this->b->processBook();
	this->repaint();
        this->makeContentsMenu();
}

void PageTemplate::keyPressEvent(QKeyEvent *event)
{
	if( event->key() == Qt::Key_Up )
	{
                if( this->b->currentPage <= this->b->utils.columnsNum-1 )
                        this->b->currentPage = this->b->pages.length()-this->b->utils.columnsNum+1;
		else
                        this->b->currentPage -= this->b->utils.columnsNum;
		this->repaint();
                this->b->saveBookPosition();
	}
	else if( event->key() == Qt::Key_Down || event->key() == Qt::Key_Space )
	{
                if( this->b->currentPage+this->b->utils.columnsNum >= this->b->pages.length() )
			this->b->currentPage = 0;
		else
                        this->b->currentPage += this->b->utils.columnsNum;
		this->repaint();
                this->b->saveBookPosition();
	}
        else if( event->key() == Qt::Key_F )
        {
            if( this->parentWidget()->isFullScreen() )
            {
                this->parentWidget()->showNormal();
                this->menuBar->show();
            }
            else
            {
                this->parentWidget()->showFullScreen();
                this->menuBar->hide();
            }
//            if( this->isFullScreen() )
//                this->showNormal();
//            else
//                this->showFullScreen();

            this->b->saveBookPosition();
        }
        else if( event->key() == Qt::Key_T )
        {
            bool ok;
            QFont font;
            font = QFontDialog::getFont(&ok, this->b->utils.paragraphFont, this);
            if(ok)
            {
                this->b->utils.paragraphFont = font;
                this->b->processBook();
                this->repaint();
                this->b->saveBookPosition();
            }
        }
        else if( event->key() == Qt::Key_1 )
        {
            this->b->utils.columnsNum = 1;
            this->b->processBook();
            this->repaint();
            this->b->saveBookPosition();
        }
        else if( event->key() == Qt::Key_2 )
        {
            this->b->utils.columnsNum = 2;
            this->b->processBook();
            this->repaint();
            this->b->saveBookPosition();
        }
        else if( event->key() == Qt::Key_3 )
        {
            this->b->utils.columnsNum = 3;
            this->b->processBook();
            this->repaint();
            this->b->saveBookPosition();
        }
//        else if( event->key() == Qt::Key_0 )
//        {
//            int isAntialiased = 0;
//            if( isAntialiased == 0 )
//                isAntialiased = 1;
//            else
//                isAntialiased = 0;
//            this->repaint();
//        }
        else if( event->key() == Qt::Key_R )
        {
            if( this->b->utils.rotateValue >= 0 && this->b->utils.rotateValue < 2)
            {
                this->b->utils.rotateValue++;
                this->b->processBook();
                this->repaint();
            }
            else
            {
                this->b->utils.rotateValue = 0;
                this->b->processBook();
                this->repaint();
            }
            this->b->saveBookPosition();
        }
}

void PageTemplate::openFile()
{
	QString filename = QFileDialog::getOpenFileName();
        this->b->bookFileName = filename;
        this->b->loadBook(filename);
        this->b->saveBookPosition();
}

void PageTemplate::setFontBigger()
{
	this->b->setFontBigger();
	this->repaint();
        this->b->saveBookPosition();
}

void PageTemplate::setFontSmaller()
{
	this->b->setFontSmaller();
	this->repaint();
        this->b->saveBookPosition();
}

void PageTemplate::setLinesBigger()
{
	this->b->setLinesBigger();
	this->repaint();
        this->b->saveBookPosition();
}

void PageTemplate::setLinesSmaller()
{
	this->b->setLinesSmaller();
	this->repaint();
        this->b->saveBookPosition();
}

void PageTemplate::setHideMenu()
{
    this->menuBar->setVisible( !this->menuBar->isVisible() );
}

void PageTemplate::showTime()
{
//    this->preparePaintEvent();
//this->update();
//        this->repaint();
}

void PageTemplate::openBookSlot()
{
        this->openFile();
}

void PageTemplate::openSettingsWindow()
{
        BookSettings *settingsWin = new BookSettings();

        settingsWin->utils = &this->b->utils;
        settingsWin->loadSettings();

        settingsWin->exec();
}

void PageTemplate::openLibrarySlot()
{
        Library *libraryWin = new Library();

//        libraryWin->utils = &this->b->utils;
//        libraryWin->loadSettings();

        libraryWin->libraryDirs = this->b->utils.libraryDirs;
        libraryWin->exec();
        QString filename = libraryWin->currentBookFilename;
        if( !filename.isEmpty() )
        {
            this->b->bookFileName = filename;
            this->b->loadBook(filename);
            this->b->saveBookPosition();
        }
}

void PageTemplate::makeContentsMenu()
{
    this->contentsMenu->clear();
    QMap<int, QString>::iterator end = this->b->bookContents.end();
    for( QMap<int, QString>::iterator iter=this->b->bookContents.begin();iter != end; ++iter )
    {
        QAction *contentsMenuAction = new QAction(iter.value(), this);
        contentsMenuAction->setObjectName( QString::number(iter.key()) );
        this->contentsMenu->addAction(contentsMenuAction);

        this->connect(contentsMenuAction, SIGNAL(triggered()), this, SLOT(openChapterSlot()));
    }
}

void PageTemplate::openChapterSlot()
{
    QObject *obj = this->sender();
    QString objname = obj->objectName();
    this->b->currentPage = this->b->getPageNum(objname.toInt());
    qDebug()<<this->b->currentPage;
}

//
