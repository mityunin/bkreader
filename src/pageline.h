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
#ifndef PAGELINE_H
#define PAGELINE_H

#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QPixmap>
#include "readerutils.h"
#include "hyphenator.h"
//

//

class TheWord 
{
public:
  int x;
  float w;
  QString data;
  TheWord();
};


class PageLine  
{

public:
	QStringList words;
        QList<TheWord> data;
//QStringList	text;
	QString		f;
	float		width;
        float           height;
        QList<int>      formatStart;
        QList<int>      formatEnd;
        QStringList     specialFormats;

	QString		indent;
	float		columnWidth;
	float		lineHeight;
	bool 		isParagraphEnd;
        QString		justify(int w, ReaderUtils utils);
        void            setPixmap(QString id, QByteArray data, int paragraphFontHeight, int w, int h);
        bool            haveFootnotes();
	
	bool		isStartParagraph;
	bool		isEndParagraph;
        bool            isPixmap;
        QStringList     footnotesId;
        QString         pixmapId;
//        QByteArray      pixmapData;
        QPixmap         pixmap;

        int lastWord;
	
	
	PageLine();
        QStringList create(QStringList words, QString indent, QString f, float w, ReaderUtils &utils, hyphenator &hyph);
};

#endif
