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
#ifndef BOOK_H
#define BOOK_H
#include <QtXml/QDomElement>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtGui/QFont>
#include <QtGui/QTextLayout>
#include "fb2.h"
#include "pageline.h"
//

//
class book  
{

public:
	book();
	void loadBook(QString filename);
	void breakLines();
        void breakFootnotes();
	//QStringList setPageLine(QStringList words);
	void makePages();
        int getPageHeight(bool getRotated=false);
	void setPageHeight(int h);
        float getColumnWidth();
        float getColumnHeight();
        float getColumnLeftCoord(int i);
        float getColumnRightCoord(int i);
	void setPageWidth(int w);
        int getPageWidth(bool getRotated=false);
        int getFootnotesHeight(QStringList footnotesId);
        PageLine getCoverpage();
	void processBook();
	void setFontBigger(int s=1);
	void setFontSmaller(int s=1);
	void setLinesBigger();
	void setLinesSmaller();
        long setCurrentWord();
        void loadTextBook(QString filename);
        void saveBookPosition();
        bool loadBookPosition();
        int getBookPositionInHistory(QString filename);
        int getParagraphWidth(int paragraphNum);
        QString getParagraphIndent(int paragraphNum);
        QStringList splitParagraph(QStringList p, QString delimiter=" ");
        QList<PageLine> getFootnotesLines(QStringList footnotesId);
        float getPageLinesHeight(QList<PageLine> pllist);
        QTextLayout::FormatRange getFormatRange(QString f, int start, int length);
        int getPageNum(int lineNum);
        QString getCurrentChapter();

	fb2 fictionbook;
        QList<QStringList> bookParagraphs;
	QList<PageLine> lines;
        QHash<QString, QList<PageLine> > footnotes;
	
        int     pageWidth;
        int     pageHeight;
        float   columnWidth;
        float   columnHeight;
//        int     leftMargin;
//        int     rightMargin;
//        int     topMargin;
//        int     bottomMargin;
//        int     citeMargin;
//        int     poemMargin;
//        int     epigraphMargin;
        int     columnsGap;
//        int     columnsNum;
        int     currentPage;
        long    currentWord;
        PageLine currentTitle;
//        int     indentValue;
//        int     rotateValue; //0 - normal, 1 - -90, 2 - 90
	QString indent;
//        QFont   paragraphFont;
//        QFont   titleFont;
//        QFont   subtitleFont;
//        QFont   citeFont;
//        QFont   footnoteFont;
//        QFont   poemFont;
//        QFont   indicatorFont;
//        float   paragraphLineSpacing;
	QList<QList<PageLine> > pages;
        QString bookFileName;
        ReaderUtils utils;
        QString authorFirstName;
        QString authorMiddleName;
        QString authorLastName;
        QString bookTitle;
        QString bookLang;
        QMap<int, QString> bookContents; //0-Name, 1-LineNum
	//QStringList paras
};
#endif
