#ifndef READERUTILS_H
#define READERUTILS_H
#include <QtCore>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QHash>
#include <QtGui/QFont>
#include <QtGui/QFontMetrics>
#include <QSettings>
//

//
class ReaderUtils  
{

public:
	ReaderUtils();
        int getWordWidth(QString key, QString f);
        void setWordWidth(QString key, int v, QString f);
        void loadHyphPatterns(QString lang);
        QStringList hyphenateWord(QString word);
        void writeSettings();
        void readSettings();
        float getLeftMargin(int i);
        float getRightMargin(int i);
        float getLeftPageIndent(int i);
        float getRightPageIndent(int i);
        float getTopPageIndent();
        float getBottomPageIndent();
//        float getPageIndent(int i=-1);

	QHash<QString, int> wordsWidths;
	QFont paragraphFont;
        QFont titleFont;
        QFont subtitleFont;
        QFont citeFont;
        QFont footnoteFont;
        QFont poemFont;
        QFont indicatorFont;
        QFont epigraphFont;
//        QFontMetrics paragraphFM;
//        QFontMetrics titleFM;
//        QFontMetrics subtitleFM;
//        QFontMetrics citeFM;
//        QFontMetrics footnoteFM;
//        QFontMetrics poemFM;
//        QFontMetrics indicatorFM;
	float paragraphLineSpacing;
        float footnoteLineSpacing;
        bool isTitleInUpperCase;
        bool hyphsIsOn;
        QHash<QString, QHash<int, int> > pats;

        int     leftMargin;
        int     rightMargin;
        int     topMargin;
        int     bottomMargin;
        int     citeMargin;
        int     poemMargin;
        int     epigraphMargin;
        int     titleTopMargin;
        int     titleBottomMargin;
        int     leftPageIndent;
        int     rightPageIndent;
        int     topPageIndent;
        int     bottomPageIndent;
        int     pageIndent;

        int     columnsGap;
        int     columnsNum;
        int     indentValue;
        int     rotateValue; //0 - normal, 1 - -90, 2 - 90
        bool    moveBigImages;
        QString bgcolor;
        QString paracolor;
//        QSettings settings;
};
#endif
