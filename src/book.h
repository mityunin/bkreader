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
	//QStringList setPageLine(QStringList words);
	void makePages();
	int getPageHeight();
	void setPageHeight(int h);
        float getColumnWidth();
        float getColumnHeight();
        float getColumnLeftCoord(int i);
        float getColumnRightCoord(int i);
	void setPageWidth(int w);
	int getPageWidth();
        int getFootnotesHeight(QStringList footnotesId);
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
        QList<PageLine> getFootnotesLines(QStringList footnotesId);
        float getPageLinesHeight(QList<PageLine> pllist);
        QTextLayout::FormatRange getFormatRange(QString f, int start, int length);
	
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
	//QStringList paras
};
#endif
