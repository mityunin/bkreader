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
#include "readerutils.h"
#include <iostream>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QHash>
#include <QtCore/QFile>
#include <QtCore/QDir>
#include <QtCore/QTextStream>
#include <QtCore/QVector>
#include <QDesktopServices>
//
ReaderUtils::ReaderUtils(  ) 
{
    this->paragraphFont.setPointSize(12);
    this->paragraphFont.setFamily("Arial");
    this->paragraphLineSpacing = 1.3;
    this->textAlign = "justify";

    this->titleFont.setPointSize(12);
    this->titleFont.setFamily("Arial");
//    this->titleFont.setBold(true);
    this->titleAlign = "center";

    this->subtitleFont.setPointSize(12);
    this->subtitleFont.setFamily("Arial");
    this->subtitleAlign = "center";

    this->citeFont.setPointSize(12);
    this->citeFont.setFamily("Arial");
    this->citeFont.setItalic(true);
    this->citeAlign = "justify";

    this->poemFont.setPointSize(12);
    this->poemFont.setFamily("Arial");
    this->poemFont.setItalic(true);
    this->poemAlign = "left";

    this->footnoteFont.setPointSize(10);
    this->footnoteFont.setFamily("Arial");
    this->footnoteFont.setItalic(true);
    this->footnoteLineSpacing = this->paragraphLineSpacing - 0.2;
    this->footnoteAlign = "justify";

    this->smallFont.setPointSize(10);
    this->smallFont.setFamily("Arial");
    this->smallFont.setItalic(false);

    this->indicatorFont.setPointSize(12);
    this->indicatorFont.setFamily("Arial");
    this->indicatorFont.setItalic(false);
    this->indicatorAlign = "justify";

    this->epigraphFont.setPointSize(12);
    this->epigraphFont.setFamily("Arial");
    this->epigraphFont.setItalic(true);
    this->epigraphAlign = "justify-right";

    this->isTitleInUpperCase    = true;
    this->hyphsIsOn             = true;
    this->indentValue           = 4;
    this->leftMargin            = 20;
    this->rightMargin           = 20;
    this->topMargin             = 20;
    this->bottomMargin          = 20;
    this->citeMargin            = 20;
    this->poemMargin            = 20;
    this->epigraphMargin        = 0;
    this->titleBottomMargin     = 2;
    this->titleTopMargin        = 2;

    this->columnsNum            = 2;
    this->columnsGap            = 20;

    this->indentValue           = 4;
    this->rotateValue           = 0;

    this->moveBigImages         = true;

    this->bgType                = "grad";
    this->bgcolor               = "#ffffff";
    this->paracolor             = "#333333";
    this->bgColorFrom           = "#ffffff";
    this->bgColorTo             = "#eeeeee";
    this->pixmapPatternFile     = "";

    this->leftPageIndent        = 8;
    this->rightPageIndent       = 8;
    this->topPageIndent         = 8;
    this->bottomPageIndent      = 8;

    this->libraryDirs.clear();

    //QString configPath = QDir::homePath()+"/.config/bkreader/bkreader.conf";
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "bkreader", "bkreader");
    QString configPath = settings.fileName();
qDebug()<<configPath;
    if(!QFile::exists(configPath))
        this->writeSettings();

    this->readSettings();
//    this->settings.set
}

int ReaderUtils::getWordWidth(QString key, QString f)
{
        if( f != "p" ) return -1;
	int v = this->wordsWidths[key];
	if( v )
	{
		return v;
	}
	return -1;
}

void ReaderUtils::setWordWidth(QString key, int v, QString f)
{
    if( f != "p" ) return;
    this->wordsWidths[key] = v;
}

void ReaderUtils::writeSettings()
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "bkreader", "bkreader");

    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    settings.setIniCodec( codec );


    settings.setValue( "fonts/paragraphFontFamily", this->paragraphFont.family() );
    settings.setValue( "fonts/paragraphPointSize", this->paragraphFont.pointSize() );
    settings.setValue( "fonts/paragraphItalic", this->paragraphFont.italic() );
    settings.setValue( "fonts/paragraphBold", this->paragraphFont.bold() );
    settings.setValue( "fonts/paragraphUnderline", this->paragraphFont.underline() );
    settings.setValue( "fonts/paragraphLineSpacing", this->paragraphLineSpacing );
    settings.setValue( "fonts/textAlign", this->textAlign );

    settings.setValue( "fonts/titleFontFamily", this->titleFont.family() );
    settings.setValue( "fonts/titlePointSize", this->titleFont.pointSize() );
    settings.setValue( "fonts/titleItalic", this->titleFont.italic() );
    settings.setValue( "fonts/titleBold", this->titleFont.bold() );
    settings.setValue( "fonts/titleUnderline", this->titleFont.underline() );
    settings.setValue( "fonts/titleAlign", this->titleAlign );

    settings.setValue( "fonts/subtitleFontFamily", this->subtitleFont.family() );
    settings.setValue( "fonts/subtitlePointSize", this->subtitleFont.pointSize() );
    settings.setValue( "fonts/subtitleItalic", this->subtitleFont.italic() );
    settings.setValue( "fonts/subtitleBold", this->subtitleFont.bold() );
    settings.setValue( "fonts/subtitleUnderline", this->subtitleFont.underline() );
    settings.setValue( "fonts/subtitleAlign", this->subtitleAlign );

    settings.setValue( "fonts/citeFontFamily", this->citeFont.family() );
    settings.setValue( "fonts/citePointSize", this->citeFont.pointSize() );
    settings.setValue( "fonts/citeItalic", this->citeFont.italic() );
    settings.setValue( "fonts/citeBold", this->citeFont.bold() );
    settings.setValue( "fonts/citeUnderline", this->citeFont.underline() );
    settings.setValue( "fonts/citeAlign", this->citeAlign );

    settings.setValue( "fonts/footnoteFontFamily", this->footnoteFont.family() );
    settings.setValue( "fonts/footnotePointSize", this->footnoteFont.pointSize() );
    settings.setValue( "fonts/footnoteItalic", this->footnoteFont.italic() );
    settings.setValue( "fonts/footnoteBold", this->footnoteFont.bold() );
    settings.setValue( "fonts/footnoteUnderline", this->footnoteFont.underline() );
    settings.setValue( "fonts/footnoteAlign", this->footnoteAlign );

    settings.setValue( "fonts/smallFontFamily", this->smallFont.family() );
    settings.setValue( "fonts/smallFontPointSize", this->smallFont.pointSize() );
    settings.setValue( "fonts/smallFontItalic", this->smallFont.italic() );
    settings.setValue( "fonts/smallFontBold", this->smallFont.bold() );
    settings.setValue( "fonts/smallFontUnderline", this->smallFont.underline() );

    settings.setValue( "fonts/poemFontFamily", this->poemFont.family() );
    settings.setValue( "fonts/poemPointSize", this->poemFont.pointSize() );
    settings.setValue( "fonts/poemItalic", this->poemFont.italic() );
    settings.setValue( "fonts/poemBold", this->poemFont.bold() );
    settings.setValue( "fonts/poemUnderline", this->poemFont.underline() );
    settings.setValue( "fonts/poemAlign", this->poemAlign );

    settings.setValue( "fonts/indicatorFontFamily", this->indicatorFont.family() );
    settings.setValue( "fonts/indicatorPointSize", this->indicatorFont.pointSize() );
    settings.setValue( "fonts/indicatorItalic", this->indicatorFont.italic() );
    settings.setValue( "fonts/indicatorBold", this->indicatorFont.bold() );
    settings.setValue( "fonts/indicatorUnderline", this->indicatorFont.underline() );
    settings.setValue( "fonts/indicatorAlign", this->indicatorAlign );

    settings.setValue( "fonts/epigraphFontFamily", this->epigraphFont.family() );
    settings.setValue( "fonts/epigraphPointSize", this->epigraphFont.pointSize() );
    settings.setValue( "fonts/epigraphItalic", this->epigraphFont.italic() );
    settings.setValue( "fonts/epigraphBold", this->epigraphFont.bold() );
    settings.setValue( "fonts/epigraphUnderline", this->epigraphFont.underline() );
    settings.setValue( "fonts/epigraphAlign", this->epigraphAlign );

    settings.setValue( "read/titleIsUppercase", this->isTitleInUpperCase );
    settings.setValue( "read/hyphsIsOn", this->hyphsIsOn );
    settings.setValue( "read/columnsNum" ,this->columnsNum );
    settings.setValue( "read/rotateValue", this->rotateValue );
    settings.setValue( "read/indentValue", this->indentValue );
    settings.setValue( "read/moveBigImages", this->moveBigImages );

    settings.setValue( "margins/leftMargin", this->leftMargin );
    settings.setValue( "margins/rightMargin", this->rightMargin );
    settings.setValue( "margins/topMargin", this->topMargin );
    settings.setValue( "margins/bottomMargin", this->bottomMargin );
    settings.setValue( "margins/citeMargin", this->citeMargin );
    settings.setValue( "margins/poemMargin", this->poemMargin );
    settings.setValue( "margins/epigraphMargin", this->epigraphMargin );
    settings.setValue( "margins/titleTopMargin", this->titleTopMargin );
    settings.setValue( "margins/titleBottomMargin", this->titleBottomMargin );

    settings.setValue( "read/bgtype", this->bgType );
    settings.setValue( "read/bgcolor", this->bgcolor );
    settings.setValue( "read/paracolor", this->paracolor );
    settings.setValue( "read/bgColorFrom", this->bgColorFrom );
    settings.setValue( "read/bgColorTo", this->bgColorTo );
    settings.setValue( "read/pixmapPatternFile", this->pixmapPatternFile );

    settings.setValue( "lastState/windowWidth", this->windowWidth );
    settings.setValue( "lastState/windowHeight", this->windowHeight );

    settings.remove( QString( "libraryDirs" ) );

    int libraryKey = 0;
    foreach(QString libraryDir, this->libraryDirs)
    {
        settings.setValue( QString("libraryDirs/")+QString::number(libraryKey), libraryDir );
        libraryKey++;
    }

    settings.sync();
}

void ReaderUtils::readSettings()
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "bkreader", "bkreader");

    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    settings.setIniCodec( codec );

    this->paragraphFont.setFamily( settings.value( "fonts/paragraphFontFamily" ).toString() );
    this->paragraphFont.setPointSize( settings.value( "fonts/paragraphPointSize" ).toInt() );
    this->paragraphFont.setItalic( settings.value( "fonts/paragraphItalic" ).toBool() );
    this->paragraphFont.setBold( settings.value( "fonts/paragraphBold" ).toBool() );
    this->paragraphFont.setUnderline( settings.value( "fonts/paragraphUnderline" ).toBool() );
    this->paragraphLineSpacing = settings.value( "fonts/paragraphLineSpacing" ).toFloat();
    this->textAlign = settings.value( "fonts/textAlign" ).toString();

    this->titleFont.setFamily( settings.value( "fonts/titleFontFamily").toString() );
    this->titleFont.setPointSize( settings.value( "fonts/titlePointSize" ).toInt() );
    this->titleFont.setItalic( settings.value( "fonts/titleItalic" ).toBool() );
    this->titleFont.setBold( settings.value( "fonts/titleBold" ).toBool() );
    this->titleFont.setUnderline( settings.value( "fonts/titleUnderline").toBool() );
    this->titleAlign = settings.value( "fonts/titleAlign" ).toString();

    this->subtitleFont.setFamily( settings.value( "fonts/subtitleFontFamily" ).toString() );
    this->subtitleFont.setPointSize( settings.value( "fonts/subtitlePointSize" ).toInt() );
    this->subtitleFont.setItalic( settings.value( "fonts/subtitleItalic" ).toBool() );
    this->subtitleFont.setBold( settings.value( "fonts/subtitleBold" ).toBool() );
    this->subtitleFont.setUnderline( settings.value( "fonts/subtitleUnderline" ).toBool() );
    this->subtitleAlign = settings.value( "fonts/subtitleAlign" ).toString();

    this->citeFont.setFamily( settings.value( "fonts/citeFontFamily" ).toString() );
    this->citeFont.setPointSize( settings.value( "fonts/citePointSize" ).toInt() );
    this->citeFont.setItalic( settings.value( "fonts/citeItalic" ).toBool() );
    this->citeFont.setBold( settings.value( "fonts/citeBold" ).toBool() );
    this->citeFont.setUnderline( settings.value( "fonts/citeUnderline" ).toBool() );
    this->citeAlign = settings.value( "fonts/citeAlign" ).toString();

    this->footnoteFont.setFamily( settings.value( "fonts/footnoteFontFamily" ).toString() );
    this->footnoteFont.setPointSize( settings.value( "fonts/footnotePointSize" ).toInt() );
    this->footnoteFont.setItalic( settings.value( "fonts/footnoteItalic" ).toBool() );
    this->footnoteFont.setBold( settings.value( "fonts/footnoteBold" ).toBool() );
    this->footnoteFont.setUnderline( settings.value( "fonts/footnoteUnderline" ).toBool() );
    this->footnoteAlign = settings.value( "fonts/footnoteAlign" ).toString();

    this->smallFont.setFamily( settings.value( "fonts/smallFontFamily" ).toString() );
    this->smallFont.setPointSize( settings.value( "fonts/smallFontPointSize" ).toInt() );
    this->smallFont.setItalic( settings.value( "fonts/smallFontItalic" ).toBool() );
    this->smallFont.setBold( settings.value( "fonts/smallFontBold" ).toBool() );
    this->smallFont.setUnderline( settings.value( "fonts/smallFontUnderline" ).toBool() );

    this->poemFont.setFamily( settings.value( "fonts/poemFontFamily" ).toString() );
    this->poemFont.setPointSize( settings.value( "fonts/poemPointSize" ).toInt() );
    this->poemFont.setItalic( settings.value( "fonts/poemItalic" ).toBool() );
    this->poemFont.setBold( settings.value( "fonts/poemBold" ).toBool() );
    this->poemFont.setUnderline( settings.value( "fonts/poemUnderline" ).toBool() );
    this->poemAlign = settings.value( "fonts/poemAlign" ).toString();

    this->indicatorFont.setFamily( settings.value( "fonts/indicatorFontFamily" ).toString() );
    this->indicatorFont.setPointSize( settings.value( "fonts/indicatorPointSize" ).toInt() );
    this->indicatorFont.setItalic( settings.value( "fonts/indicatorItalic" ).toBool() );
    this->indicatorFont.setBold( settings.value( "fonts/indicatorBold" ).toBool() );
    this->indicatorFont.setUnderline( settings.value( "fonts/indicatorUnderline" ).toBool() );
    QFontMetrics *indicatorFM = new QFontMetrics(this->indicatorFont);
    this->indicatorFontHeight = indicatorFM->height()*this->paragraphLineSpacing + 5;
    this->indicatorAlign = settings.value( "fonts/indicatorAlign" ).toString();

    this->epigraphFont.setFamily( settings.value( "fonts/epigraphFontFamily" ).toString() );
    this->epigraphFont.setPointSize( settings.value( "fonts/epigraphPointSize" ).toInt() );
    this->epigraphFont.setItalic( settings.value( "fonts/epigraphItalic" ).toBool() );
    this->epigraphFont.setBold( settings.value( "fonts/epigraphBold" ).toBool() );
    this->epigraphFont.setUnderline( settings.value( "fonts/epigraphUnderline" ).toBool() );
    this->epigraphAlign = settings.value( "fonts/epigraphAlign" ).toString();

    this->isTitleInUpperCase = settings.value( "read/titleIsUppercase").toBool();
    this->hyphsIsOn = settings.value( "read/hyphsIsOn" ).toBool();
    this->columnsNum = settings.value( "read/columnsNum" ).toInt();
    this->rotateValue = settings.value( "read/rotateValue" ).toInt();
    this->indentValue = settings.value( "read/indentValue").toInt();

    this->leftMargin = settings.value( "margins/leftMargin" ).toInt();
    this->rightMargin = settings.value( "margins/rightMargin" ).toInt();
    this->topMargin = settings.value( "margins/topMargin" ).toInt();
    this->bottomMargin = settings.value( "margins/bottomMargin" ).toInt();
    this->citeMargin = settings.value( "margins/citeMargin" ).toInt();
    this->poemMargin = settings.value( "margins/poemMargin" ).toInt();
    this->epigraphMargin = settings.value( "margins/epigraphMargin" ).toInt();
    this->titleTopMargin = settings.value( "margins/titleTopMargin" ).toInt();
    this->titleBottomMargin = settings.value( "margins/titleBottomMargin" ).toInt();

	if( this->indicatorFontHeight > this->topMargin )
        this->indicatorFontHeight = this->topMargin;

        this->bgType = settings.value( "read/bgtype").toString();
        this->pixmapPatternFile = settings.value( "read/pixmapPatternFile" ).toString();
    this->bgcolor = settings.value( "read/bgcolor" ).toString();
    this->paracolor = settings.value( "read/paracolor" ).toString();
    this->bgColorFrom = settings.value( "read/bgColorFrom" ).toString();
    this->bgColorTo = settings.value( "read/bgColorTo" ).toString();

    this->moveBigImages = settings.value( "read/moveBigImages" ).toBool();

    this->libraryDirs.clear();
    settings.beginGroup( "libraryDirs" );
    QStringList libraryKeys = settings.allKeys();
    settings.endGroup();
    foreach( QString libraryKey, libraryKeys )
    {
        QString libraryDir = settings.value( QString("libraryDirs/")+libraryKey, QString("") ).toString();
        if( !libraryDir.isEmpty() )
            this->libraryDirs.append( libraryDir );
    }
}

float ReaderUtils::getLeftMargin(int i, bool getRotated)
{
    if(i == 1)
    {
//        if( getRotated && this->rotateValue != 0 )
//            return this->topMargin;
//        else
            return this->rightMargin;
    }
    else
    {
//        if( getRotated && this->rotateValue != 0 )
//            return this->bottomMargin;
//        else
            return this->leftMargin;
    }
}


float ReaderUtils::getRightMargin(int i, bool getRotated)
{
    if(i == 1)
    {
//        if( getRotated && this->rotateValue != 0 )
//            return this->bottomMargin;
//        else
            return this->leftMargin;
    }
    else
    {
//        if( getRotated && this->rotateValue != 0 )
//            return this->topMargin;
//        else
            return this->rightMargin;
    }
}

float ReaderUtils::getLeftPageIndent(int i)
{
    if( i == 0 )
        return this->leftPageIndent;
    else
        return this->leftPageIndent/2;
}

float ReaderUtils::getRightPageIndent(int i)
{
    if( i == this->columnsNum-1 )
        return this->rightPageIndent;
    else
        return this->rightPageIndent/2;
}

float ReaderUtils::getTopPageIndent()
{
    return this->topPageIndent;
}

float ReaderUtils::getBottomPageIndent()
{
    return this->bottomPageIndent;
}

//
