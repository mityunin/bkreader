#ifndef PAGELINE_H
#define PAGELINE_H

#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QPixmap>
#include "readerutils.h"
#include "hyphenator.h"
//

//
class PageLine  
{

public:
	QStringList words;
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
