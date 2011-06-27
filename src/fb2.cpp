#include "fb2.h"
#include <iostream>
#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>
#include <QtXml/QDomNode>
#include <QtGui>
#include <QtCore>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QFile>
//
fb2::fb2(  ) 
{
	// TODO
}
//

void fb2::loadFB2(QString filename)
{
	this->bookFormats.clear();
	this->bookParagraphs.clear();
        this->coverPageId.clear();
        this->binarys.clear();
        this->authorFirstName.clear();
        this->authorLastName.clear();
        this->authorMiddleName.clear();
        this->contents.clear();
//        this->currentWord = 0;
	
	QDomDocument doc("fb2");
	//QFile f("/home/sa/bookc/test.fb2");
	QFile f(filename);
	if(!f.open(QIODevice::ReadOnly))
		return;
	if(!doc.setContent(&f))
	{
		f.close();
		return;
	}
	f.close();
	
        const QDomElement docElement = doc.documentElement();

        QDomElement element = docElement.firstChildElement();
        while( !element.isNull() )
        {
            if( element.tagName() == QLatin1String( "binary" ) )
            {
                this->loadBinary( element );
            }
            element = element.nextSiblingElement();
        }

	QStringList bookParagraphs;
        element = docElement.firstChildElement();
	while( !element.isNull() )
	{
                if( element.tagName() == QLatin1String( "body" ) )
		{
			this->loadBody(element);
		}
                else if( element.tagName() == QLatin1String( "description" ) )
                {
                        this->loadDescription(element);
                }
		
		element = element.nextSiblingElement();
	}
}

void fb2::loadSection(const QDomElement &element)
{
        QString sectionId = element.attribute(QString("id"));

        if( !sectionId.isEmpty() )
        {
            QStringList footnoteTitle;
            QStringList footnoteParagraph;

            QDomElement child = element.firstChildElement();
            while( !child.isNull() )
            {
                    if ( child.tagName() == QLatin1String( "p" ) )
                    {
                            footnoteParagraph = this->loadFootnoteParagraph( child );
                    }
                    else if( child.tagName() == QLatin1String( "title" ) )
                    {
                            footnoteTitle = this->loadFootnoteTitle( child );
                    }

                    this->footnotes[ "#"+sectionId ]["title"]   = footnoteTitle;
                    this->footnotes[ "#"+sectionId ]["p"]       = footnoteParagraph;

                    child = child.nextSiblingElement();
            }

            footnoteTitle.clear();
            footnoteParagraph.clear();
            sectionId.clear();
//            qDebug()<<this->footnotes;
            return;
        }

	QDomElement child = element.firstChildElement();
	while( !child.isNull() )
	{
		if ( child.tagName() == QLatin1String( "p" ) )
		{
                        this->loadParagraph( child );
		}
		else if( child.tagName() == QLatin1String( "section" ) )
		{
                        this->loadSection( child );
		}
		else if( child.tagName() == QLatin1String( "title" ) )
		{
			this->loadTitle( child );
		}
		else if( child.tagName() == QLatin1String( "subtitle" ) )
		{
			this->loadSubtitle( child );
		}
		else if( child.tagName() == QLatin1String( "epigraph" ) )
		{
                        this->bookParagraphs.append( QStringList( "" ) );
                        this->bookFormats.append( QStringList( "epigraph" ) );
			
			this->loadEpigraph( child );

                        this->bookParagraphs.append( QStringList( "" ) );
                        this->bookFormats.append( QStringList( "epigraph" ) );
		}
		else if( child.tagName() == QLatin1String( "cite" ) )
		{
                        this->bookParagraphs.append( QStringList( "" ) );
                        this->bookFormats.append( QStringList( "cite" ) );

			this->loadCite( child );
                        //this->bookFormats.append( QStringList( "cite" ) );
			
                        this->bookParagraphs.append( QStringList( "" ) );
                        this->bookFormats.append( QStringList( "cite" ) );
		}
                else if( child.tagName() == QLatin1String( "image" ) )
                {
                    QString imageId = child.attribute( "l:href" );
                    imageId = imageId.right( imageId.count()-1 );
                    this->bookParagraphs.append(QStringList( imageId ));
                    this->bookFormats.append(QStringList( "image" ));
                }
                else if( child.tagName() == QLatin1String( "empty-line" ) )
                {
                    this->bookParagraphs.append( QStringList( "" ) );
                    this->bookFormats.append( QStringList( "empty-line" ) );
//                    this->bookFormats.append( QStringList( "" ) );
                }
                else if( child.tagName() == QLatin1String( "poem" ) )
                {
                    this->loadPoem(child);
                }
		//qDebug() << "Next";
		child = child.nextSiblingElement();
	}
}

void fb2::loadParagraph(const QDomElement &element)
{
	QDomNode child = element.firstChild();
	QStringList paragraph;
	QStringList formats;
        int startFootnote = 0;
        int endFootnote = 0;
	while( !child.isNull() )
	{
		if( child.isText() )
		{
			QDomText text = child.toText();
			if ( !text.isNull() )
                        {
                            paragraph.append( QStringList(text.data().trimmed()) );
                            formats.append( QStringList("p") );
                            startFootnote += text.data().trimmed().split(" ").size();
			}
		}
		else if( child.isElement() )
                {
			QDomElement childElement = child.toElement();
			if( childElement.tagName() == QLatin1String( "a" ) )
                        {
                            QString footnoteId = childElement.attribute(QString("l:href"));
				QDomNode childNode = child.firstChild();
				if( childNode.isText() )
				{
					QDomText childText = childNode.toText();
					if( !childText.isNull() )
					{
//                                            QStringList txt = QStringList(childText.data().replace(QRegExp(QString::fromUtf8("-")), QString::fromUtf8("---")));
                //                            QBool cont = txt.contains(QString("е"));
                //                            paragraph.append( QStringList(text.data().trimmed()) );
//                                            paragraph.append(txt);
                                                paragraph.append( QStringList(childText.data().trimmed()) );
                                                formats.append( QStringList("footnote:"+footnoteId) );
                                                endFootnote = startFootnote + childText.data().trimmed().split(" ").size();
                                                this->footnotesRange[footnoteId].append(startFootnote);
                                                this->footnotesRange[footnoteId].append(endFootnote);
                                                int test = 0;
//                                                this->currentWord += childText.data().trimmed().split(" ").count();
					}
				}
			}
			else
			{
				QDomNode childNode = child.firstChild();
				if( childNode.isText() )
				{
					QDomText childText = childNode.toText();
					if( !childText.isNull() )
					{
//                                            QStringList txt = QStringList(childText.data().replace(QRegExp(QString::fromUtf8("-")), QString::fromUtf8("---")));
                //                            QBool cont = txt.contains(QString("е"));
                //                            paragraph.append( QStringList(text.data().trimmed()) );
//                                            paragraph.append(txt);
                                                paragraph.append( QStringList(childText.data().trimmed()) );
						formats.append( QStringList("p") );
                                                startFootnote += childText.data().trimmed().split(" ").size();
//                                                this->currentWord += childText.data().trimmed().split(" ").count();
					}
				}
			}
		}
	
		child = child.nextSibling();
	}

	this->bookParagraphs.append(paragraph);
	this->bookFormats.append( formats );
//        this->footnotes
	paragraph.clear();
}

void fb2::loadBody(const QDomElement &element)
{
	QDomElement child = element.firstChildElement();
	while( !child.isNull() ){
		if ( child.tagName() == QLatin1String("section") )
		{
			this->loadSection(child);
		}
		child = child.nextSiblingElement();
		
	}
}

void fb2::loadTitle(const QDomElement &element)
{
        QStringList titleForContents;
	QDomElement child = element.firstChildElement();
	while( !child.isNull() )
	{
		if( child.tagName() == QLatin1String( "p" ))
		{
			QDomNode node = child.firstChild();
			while( !node.isNull() )
			{
				if( node.isText() )
				{
					QDomText text = node.toText();
					if( !text.isNull() )
					{
//						this->bookParagraphs.append( QStringList("") );
//						this->bookFormats.append( QStringList("title") );
						
                                                this->bookParagraphs.append( QStringList(text.data().trimmed()) );
						this->bookFormats.append( QStringList("title") );
//                                                this->currentWord += text.data().trimmed().split(" ").count();
//                                                titleForContents.append( QStringList(text.data().trimmed()) );
                                                this->contents.append( QStringList(text.data().trimmed()) );
//						this->bookParagraphs.append( QStringList("") );
//						this->bookFormats.append( QStringList("title") );
					}
				}
				node = node.nextSibling();
			}
		}
		child = child.nextSiblingElement();
	}

//        this->contents[this->currentWord] = QStringList(titleForContents.at(0));
//        this->contents.insert(titleForContents, this->currentWord);
}

void fb2::loadSubtitle(const QDomElement &element)
{
	QDomNode child = element.firstChild();
	while( !child.isNull() )
	{
		if( child.isText() )
		{
			QDomText text = child.toText();
			if( !text.isNull() )
			{
//				this->bookParagraphs.append( QStringList("") );
//				this->bookFormats.append( QStringList("subtitle") );
				
                                this->bookParagraphs.append( QStringList(text.data().trimmed()) );
				this->bookFormats.append( QStringList("subtitle") );
//                                this->currentWord += text.data().trimmed().split(" ").count();
				
//				this->bookParagraphs.append( QStringList("") );
//				this->bookFormats.append( QStringList("subtitle") );
			}
		}
		child = child.nextSibling();
	}
}

void fb2::loadEpigraph(const QDomElement &element)
{
	QDomElement child = element.firstChildElement();
	while( !child.isNull() )
	{
		if( child.tagName() == QLatin1String( "p" ))
		{
			QDomNode node = child.firstChild();
			while( !node.isNull() )
			{
				if( node.isText() )
				{
					QDomText text = node.toText();
					if( !text.isNull() )
					{
                                                this->bookParagraphs.append( QStringList(text.data().trimmed()) );
						this->bookFormats.append( QStringList("epigraph") );
//                                                this->currentWord += text.data().trimmed().split(" ").count();
					}
				}
				node = node.nextSibling();
			}
		}
		child = child.nextSiblingElement();
	}
}

void fb2::loadCite(const QDomElement &element)
{
	QDomElement child = element.firstChildElement();
	while( !child.isNull() )
	{
		if( child.tagName() == QLatin1String( "p" ))
		{
			QDomNode node = child.firstChild();
			while( !node.isNull() )
			{
				if( node.isText() )
				{
					QDomText text = node.toText();
					if( !text.isNull() )
					{
                                                this->bookParagraphs.append( QStringList(text.data().trimmed()) );
						this->bookFormats.append( QStringList("cite") );
//                                                this->currentWord += text.data().trimmed().split(" ").count();
					}
				}
				node = node.nextSibling();
			}
		}
		child = child.nextSiblingElement();
	}
}

QList<QStringList> fb2::getRawParagraphs()
{
	return this->bookParagraphs;
}

void fb2::loadBinary(const QDomElement &element)
{
//    QDomNode child = element.firstChild();
//    qDebug() << element.nodeType();
    const QDomText text = element.firstChild().toText();
    QByteArray data = text.data().toLatin1();
    data = QByteArray::fromBase64( data );
    this->binarys[ element.attribute("id") ] = data;
}

void fb2::loadDescription(const QDomElement &element)
{
    QDomElement child = element.firstChildElement();
    while( !child.isNull() )
    {
        if( child.tagName() == QLatin1String( "title-info" ) )
        {
            this->loadTitleInfo(child);
        }
        child = child.nextSiblingElement();
    }
}

void fb2::loadTitleInfo(const QDomElement &element)
{
    QDomElement child = element.firstChildElement();
    while( !child.isNull() )
    {
        if( child.tagName() == QLatin1String( "coverpage" ) )
        {
            this->loadCoverPage(child);
        }
        child = child.nextSiblingElement();
    }
}

void fb2::loadCoverPage(const QDomElement &element)
{
    QDomElement child = element.firstChildElement();
    QString id = child.attribute( "l:href" );
    this->coverPageId = id.right( id.count() - 1 );
}

void fb2::loadPoem(const QDomElement &element)
{
    QDomElement child = element.firstChildElement();
    if( child.tagName() != QLatin1String( "stanza" ) ) return;
    while( !child.isNull() )
    {
        this->bookParagraphs.append( QStringList( "" ) );
        this->bookFormats.append( QStringList( "poem" ) );

        this->loadStanza(child);

        this->bookParagraphs.append( QStringList( "" ) );
        this->bookFormats.append( QStringList( "poem" ) );

        child = child.nextSiblingElement();
    }
}

void fb2::loadStanza(const QDomElement &element)
{
    QDomElement child = element.firstChildElement();
    while( !child.isNull() )
    {
        if( child.tagName() == QLatin1String( "v" ) )
        {
            this->loadStanzaV(child);
        }
        child = child.nextSiblingElement();
    }
}

void fb2::loadStanzaV(const QDomElement &element)
{
    QDomNode child = element.firstChild();
    QStringList paragraph;
    QStringList formats;
    while( !child.isNull() )
    {
            if( child.isText() )
            {
                    QDomText text = child.toText();
                    if ( !text.isNull() )
                    {
                            paragraph.append( QStringList(text.data().trimmed()) );
                            formats.append( QStringList("poem") );
//                            this->currentWord += text.data().trimmed().split(" ").count();
                    }
            }
            else if( child.isElement() )
            {
                    QDomElement childElement = child.toElement();
                    if( childElement.tagName() == QLatin1String( "a" ) )
                    {
                            QDomNode childNode = child.firstChild();
                            if( childNode.isText() )
                            {
                                    QDomText childText = childNode.toText();
                                    if( !childText.isNull() )
                                    {
                                            paragraph.append( QStringList(childText.data().trimmed()) );
                                            formats.append( QStringList("footnote") );
//                                            this->currentWord += childText.data().trimmed().split(" ").count();
                                    }
                            }
                    }
                    else
                    {
                            QDomNode childNode = child.firstChild();
                            if( childNode.isText() )
                            {
                                    QDomText childText = childNode.toText();
                                    if( !childText.isNull() )
                                    {
                                            paragraph.append( QStringList(childText.data().trimmed()) );
                                            formats.append( QStringList("poem") );
//                                            this->currentWord += childText.data().trimmed().split(" ").count();
                                    }
                            }
                    }
            }

            child = child.nextSibling();
    }

    this->bookParagraphs.append(paragraph);
    this->bookFormats.append( formats );
    paragraph.clear();
}

QStringList fb2::loadFootnoteTitle(const QDomElement &element)
{
        QStringList footnoteTitle;
        QDomElement child = element.firstChildElement();
//        qDebug()<<child.tagName();
        while( !child.isNull() )
        {
//            qDebug()<<child.tagName();
                if( child.tagName() == QLatin1String( "p" ))
                {
                        QDomNode node = child.firstChild();
                        while( !node.isNull() )
                        {
                                if( node.isText() )
                                {
                                        QDomText text = node.toText();
                                        if( !text.isNull() )
                                        {
                                                footnoteTitle.append( QStringList(text.data().trimmed()) );
//                                                this->currentWord += text.data().trimmed().split(" ").count();
                                        }
                                }
                                node = node.nextSibling();
                        }
                }
                child = child.nextSiblingElement();
        }

        return footnoteTitle;
}

QStringList fb2::loadFootnoteParagraph(const QDomElement &element)
{
        QDomNode child = element.firstChild();
        QStringList paragraph;
        while( !child.isNull() )
        {
                if( child.isText() )
                {
                        QDomText text = child.toText();
                        if ( !text.isNull() )
                        {
                            paragraph.append( QStringList(text.data().trimmed()) );
//                            this->currentWord += text.data().trimmed().split(" ").count();
                        }
                }
                else if( child.isElement() )
                {
                        QDomElement childElement = child.toElement();
                        QDomNode childNode = child.firstChild();
                        if( childNode.isText() )
                        {
                                QDomText childText = childNode.toText();
                                if( !childText.isNull() )
                                {
                                        paragraph.append( QStringList(childText.data().trimmed()) );
//                                        this->currentWord += childText.data().trimmed().split(" ").count();
                                }
                        }
                }

                child = child.nextSibling();
        }
        return paragraph;
}
