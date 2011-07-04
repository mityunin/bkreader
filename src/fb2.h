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
