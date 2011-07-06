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
#ifndef FB2_H
#define FB2_H
#include <QtXml/QDomElement>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QHash>
#include <QtCore/QRegExp>
//

//
class fb2  
{

public:
	fb2();
	void loadFB2(QString filename);
	void loadSection(const QDomElement &element);
	void loadBody(const QDomElement &element);
	void loadParagraph(const QDomElement &element);
	void loadTitle(const QDomElement &element);
	void loadSubtitle(const QDomElement &element);
	void loadEpigraph(const QDomElement &element);
	void loadCite(const QDomElement &element);
        void loadBinary(const QDomElement &element);
        void loadDescription(const QDomElement &element);
        void loadTitleInfo(const QDomElement &element);
        void loadCoverPage(const QDomElement &element);
        void loadPoem(const QDomElement &element);
        void loadStanza(const QDomElement &element);
        void loadStanzaV(const QDomElement &element);
        QStringList loadFootnoteTitle(const QDomElement &element);
        QStringList loadFootnoteParagraph(const QDomElement &element);
	QList<QStringList> getRawParagraphs();
	
	
	QList<QStringList> bookParagraphs;
	QList<QStringList> bookFormats;
        QHash<QString, QByteArray> binarys;
        QHash<QString, QHash<QString, QStringList> > footnotes;
        QHash<QString, QList<int> > footnotesRange;
        QString coverPageId;
        QString authorFirstName;
        QString authorMiddleName;
        QString authorLastName;
        QString bookTitle;
        QString bookLang;
//        QHash<long, QStringList> contents;
        QStringList contents;

private:
        long currentWord;

};
#endif
