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
#ifndef READERUTILS_H
#define READERUTILS_H
#include <QtCore>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QHash>
#include <QtGui/QFont>
#include <QtGui/QFontMetrics>
#include <QSettings>
#include <QTextCodec>
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
        float getLeftMargin(int i, bool getRotated=true);
        float getRightMargin(int i, bool getRotated=true);
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
        QString pixmapPatternFile;
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
        float   indicatorFontHeight;

        int     columnsGap;
        int     columnsNum;
        int     indentValue;
        int     rotateValue; //0 - normal, 1 - -90, 2 - 90
        bool    moveBigImages;
        QString bgType;
        QString bgcolor;
        QString bgColorFrom;
        QString bgColorTo;
        QString paracolor;
        QStringList libraryDirs;
//        QSettings settings;
};
#endif
