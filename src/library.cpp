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
#include "library.h"
#include "ui_library.h"
#include <QTreeView>
#include <QTreeWidget>
#include <QDir>
#include <QFile>
#include <QDirIterator>
#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>
#include <QtXml/QDomNode>
#include "osdab-zip/unzip.h"
#include <QSettings>
#include <QTextCodec>

Library::Library(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Library)
{
    ui->setupUi(this);
    this->currentBookFilename.clear();
    this->readLibrary();
    this->showLibrary();
}

Library::~Library()
{
    delete ui;
}

void Library::on_butRefreshLibrary_clicked()
{
    this->bookAuthors.clear();
    this->bookExtensions.clear();
    this->bookFilenames.clear();
    this->bookLangs.clear();
    this->bookNames.clear();

    QStringList fileFilters;
    fileFilters.append(QString("*.fb2"));
    fileFilters.append(QString("*.txt"));
    fileFilters.append(QString("*.zip"));

    QDirIterator dir_iterator(QString( "/home/sa/FBooks" ), fileFilters, QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories );
    while( dir_iterator.hasNext() )
    {
        dir_iterator.next();
//        this->bookFilenames[dir_iterator.fileInfo().absoluteFilePath()] = dir_iterator.fileName();

        if( dir_iterator.fileInfo().suffix() == QLatin1String("fb2") )
        {
            QStringList fb2info = this->loadFB2FileInfo(dir_iterator.fileInfo().absoluteFilePath());
            this->bookNames[dir_iterator.fileInfo().absoluteFilePath()] = fb2info[0];
            this->bookAuthors[dir_iterator.fileInfo().absoluteFilePath()] = fb2info[1];
            this->bookLangs[dir_iterator.fileInfo().absoluteFilePath()] = fb2info[2];
            this->bookExtensions[dir_iterator.fileInfo().absoluteFilePath()] = QString("fb2");
            this->bookFilenames[dir_iterator.fileInfo().absoluteFilePath()] = dir_iterator.fileInfo().absoluteFilePath();
            this->bookCoverpages[dir_iterator.fileInfo().absoluteFilePath()] = fb2info[3];
        }
        else if( dir_iterator.fileInfo().suffix() == QLatin1String("txt") )
        {
            this->bookNames[dir_iterator.fileInfo().absoluteFilePath()] = dir_iterator.fileName();
            this->bookAuthors[dir_iterator.fileInfo().absoluteFilePath()] = QString("");
            this->bookLangs[dir_iterator.fileInfo().absoluteFilePath()] = QString("");
            this->bookExtensions[dir_iterator.fileInfo().absoluteFilePath()] = QString("txt");
            this->bookFilenames[dir_iterator.fileInfo().absoluteFilePath()] = dir_iterator.fileInfo().absoluteFilePath();
            this->bookCoverpages[dir_iterator.fileInfo().absoluteFilePath()] = QString("");
        }
        else if( dir_iterator.fileInfo().suffix() == QLatin1String("zip") )
        {
            UnZip unzip;
            UnZip::ErrorCode ec = unzip.openArchive(dir_iterator.fileInfo().absoluteFilePath());

            if( ec != UnZip::Ok )
                continue;

            QStringList filesInArchive = unzip.fileList();

            if( filesInArchive.count() > 0 )
            {
                if( filesInArchive.at(0).contains(QString(".fb2")) )
                {
                    QString filename = filesInArchive.at(0);
                    ec = unzip.extractFile(filename, QDir::tempPath());
                    if( ec == UnZip::Ok )
                    {
                        filename = QDir::tempPath()+QString("/")+filename;
                        unzip.closeArchive();
                        QStringList fb2info = this->loadFB2FileInfo(filename);
                        this->bookNames[dir_iterator.fileInfo().absoluteFilePath()] = fb2info[0];
                        this->bookAuthors[dir_iterator.fileInfo().absoluteFilePath()] = fb2info[1];
                        this->bookLangs[dir_iterator.fileInfo().absoluteFilePath()] = fb2info[2];
                        this->bookExtensions[dir_iterator.fileInfo().absoluteFilePath()] = QString("zip/fb2");
                        this->bookFilenames[dir_iterator.fileInfo().absoluteFilePath()] = dir_iterator.fileInfo().absoluteFilePath();
                        this->bookCoverpages[dir_iterator.fileInfo().absoluteFilePath()] = fb2info[3];
                    }
                }
                else
                {
                    continue;
                }
            }
        }
    }

    this->writeLibrary();
    this->showLibrary();

}

QStringList Library::loadFB2FileInfo(QString filename)
{
    QStringList fb2info; //0 - bookName, 1 - bookAuthor, 2 - lang, 3 - coverpage
    fb2info.append("Unknown");
    fb2info.append("Unknown");
    fb2info.append("ru");
    fb2info.append("");

    QString authorFirstName;
    QString authorMiddleName;
    QString authorLastName = "Unknown";

    QDomDocument doc("fb2");
    //QFile f("/home/sa/bookc/test.fb2");
    QFile f(filename);
    if(!f.open(QIODevice::ReadOnly))
        return fb2info;
    if(!doc.setContent(&f))
    {
            f.close();
            return fb2info;
    }
    f.close();

    const QDomElement docElement = doc.documentElement();

    QDomElement element = docElement.firstChildElement();
    while( !element.isNull() )
    {
        if( element.tagName() == QLatin1String( "binary" ) )
        {
//            this->loadBinary( element );
        }
        element = element.nextSiblingElement();
    }

//    QStringList bookParagraphs;
    element = docElement.firstChildElement();
    while( !element.isNull() )
    {
            if( element.tagName() == QLatin1String( "body" ) )
            {
//                    this->loadBody(element);
            }
            else if( element.tagName() == QLatin1String( "description" ) )
            {
//                    this->loadDescription(element);
                QDomElement childDescription = element.firstChildElement();
                while( !childDescription.isNull() )
                {
                    if( childDescription.tagName() == QLatin1String( "title-info" ) )
                    {
                        QDomElement childTitle = childDescription.firstChildElement();
                        while( !childTitle.isNull() )
                        {
                            if( childTitle.tagName() == QLatin1String( "coverpage" ) )
                            {
//                                this->loadCoverPage(child);
                                QDomElement childCoverpage = childTitle.firstChildElement();
                                QString id = childCoverpage.attribute( "l:href" );
                                fb2info[3] = id.right( id.count() - 1 );
                            }
                            else if( childTitle.tagName() == QLatin1String( "author" ) )
                            {
                                QDomElement childTitleElement = childTitle.firstChildElement();
                                while( !childTitleElement.isNull() )
                                {
                                    if( childTitleElement.tagName() == QLatin1String("first-name") )
                                    {
                                        QDomNode textNode = childTitleElement.firstChild();
                                        authorFirstName = textNode.toText().data().trimmed();
                                    }
                                    else if( childTitleElement.tagName() == QLatin1String("middle-name") )
                                    {
                                        QDomNode textNode = childTitleElement.firstChild();
                                        authorMiddleName = textNode.toText().data().trimmed();
                                    }
                                    else if( childTitleElement.tagName() == QLatin1String("last-name") )
                                    {
                                        QDomNode textNode = childTitleElement.firstChild();
                                        authorLastName = textNode.toText().data().trimmed();
                                    }
                                    childTitleElement = childTitleElement.nextSiblingElement();
                                }

                            }
                            else if( childTitle.tagName() == QLatin1String( "book-title" ) )
                            {
                                QDomNode childNode = childTitle.firstChild();
                                fb2info[0] = childNode.toText().data().trimmed();
                    //            int test = 0;
                            }
                            else if( childTitle.tagName() == QLatin1String( "lang" ) )
                            {
                                QDomNode childNode = childTitle.firstChild();
                                fb2info[2] = childNode.toText().data().trimmed();
                                int test = 0;
                            }
                            childTitle = childTitle.nextSiblingElement();
                        }
                    }
                    childDescription = childDescription.nextSiblingElement();
                }
            }

            element = element.nextSiblingElement();
    }

//     = authorLastName + " " + authorFirstName + " " + authorMiddleName;
    QStringList author;
    author.append(authorLastName);
    author.append(authorFirstName);
    author.append(authorMiddleName);
    fb2info[1] = author.join(" ");

    return fb2info;
}

void Library::writeLibrary()
{
    QSettings settings( "bkreader", "library" );
    settings.clear();
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    settings.setIniCodec( codec );
    QStringList keys = this->bookFilenames.keys();
    foreach(QString key, keys)
    {
        settings.setValue( QString("bookNames/")+key, this->bookNames[key] );
        settings.setValue( QString("bookAuthors/"+key), this->bookAuthors[key] );
        settings.setValue( QString("bookExtensions/"+key), this->bookExtensions[key] );
        settings.setValue( QString("bookLangs/"+key), this->bookLangs[key] );
        settings.setValue( QString("bookFilenames/"+key), this->bookFilenames[key] );
        settings.setValue( QString("bookCoverpages/"+key), this->bookCoverpages[key] );
    }
}

void Library::readLibrary()
{
    QSettings settings( "bkreader", "library" );
    this->bookAuthors.clear();
    this->bookExtensions.clear();
    this->bookFilenames.clear();
    this->bookLangs.clear();
    this->bookNames.clear();

    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    settings.setIniCodec( codec );

    settings.beginGroup("bookNames");
    QStringList keys = settings.allKeys();
    settings.endGroup();
    keys.removeDuplicates();
    foreach(QString key, keys)
    {
        this->bookAuthors[key] = settings.value( QString("bookAuthors/")+key ).toString();
        this->bookExtensions[key] = settings.value( QString("bookExtensions/")+key ).toString();
        this->bookLangs[key] = settings.value( QString("bookLangs/")+key ).toString();
        this->bookNames[key] = settings.value( QString("bookNames/")+key ).toString();
        this->bookFilenames[key] = settings.value( QString("bookFilenames/")+key ).toString();
        this->bookCoverpages[key] = settings.value( QString("bookCoverpages/")+key ).toString();
    }
}

void Library::showLibrary()
{
    this->ui->treeBookLibrary->clear();
    this->ui->treeBookLibrary->setHeaderLabels(QStringList());
    QStringList bookAuthorsValues = this->bookAuthors.values();
    bookAuthorsValues.removeDuplicates();
    qSort(bookAuthorsValues);
    foreach(QString bookAuthorValue, bookAuthorsValues)
    {
        QStringList bookAuthorKeys = this->bookAuthors.keys(bookAuthorValue);
        QTreeWidgetItem *itemAuthor = new QTreeWidgetItem(this->ui->treeBookLibrary);
        itemAuthor->setText(0, bookAuthorValue);
        foreach(QString bookAuthorKey, bookAuthorKeys)
        {
            QTreeWidgetItem *itemBookName = new  QTreeWidgetItem(itemAuthor);
            itemBookName->setText( 0, this->bookNames[bookAuthorKey] );
            itemBookName->setText( 1, bookAuthorKey );
        }
    }
}

void Library::on_treeBookLibrary_itemClicked(QTreeWidgetItem *item, int column)
{
    QString key = item->text(1);
    QString bookName = this->bookNames[key];
    QString bookAuthor = this->bookAuthors[key];
    QString bookExtension = this->bookExtensions[key];
    QString bookLang = this->bookLangs[key];
    QString bookFilename = this->bookFilenames[key];
    QString bookCoverpage = this->bookCoverpages[key];

    this->ui->labBookAuthor->setText(bookAuthor);
    this->ui->labBookName->setText(bookName);
    this->ui->labBookExtension->setText(bookExtension);
    this->ui->labBookLang->setText(bookLang);
    this->ui->labFilename->setText(bookFilename);

    if( !bookFilename.isEmpty() )
        this->currentBookFilename = bookFilename;
    else
        this->currentBookFilename.clear();

    if( !bookCoverpage.isEmpty() )
    {
        QByteArray coverpage = this->loadFB2Coverpage(bookCoverpage, bookFilename);
        if( !coverpage.isEmpty() )
        {
            QPixmap pixmap;
            pixmap.loadFromData(coverpage);
            int h = this->ui->gvBookCoverpage->height();
            int w = this->ui->gvBookCoverpage->width();

            int hp = pixmap.height();
            int wp = pixmap.width();
            int aspectp = float(wp)/hp;

            if( aspectp <= 1 )
            {
                pixmap = pixmap.scaledToHeight(h);
                if( pixmap.width() > w )
                    pixmap = pixmap.scaledToWidth(w);
            }
            else
            {
                pixmap = pixmap.scaledToWidth(w);
                if( pixmap.height() > h )
                    pixmap = pixmap.scaledToHeight(h);
            }

            QGraphicsScene *scene = new QGraphicsScene();
            this->ui->gvBookCoverpage->setScene(scene);
            scene->addPixmap(pixmap);
        }
        else
        {
            QGraphicsScene *scene = new QGraphicsScene();
            this->ui->gvBookCoverpage->setScene(scene);
        }
    }
    else
    {
        QGraphicsScene *scene = new QGraphicsScene();
        this->ui->gvBookCoverpage->setScene(scene);
        int test=0;
    }
}

void Library::on_butLoadBook_clicked()
{
    this->close();
}

void Library::on_butClose_clicked()
{
    this->currentBookFilename.clear();
    this->close();
}

QByteArray Library::loadFB2Coverpage(QString id, QString filename)
{

    if( filename.right(3) == QLatin1String("zip") )
    {
        UnZip unzip;
        UnZip::ErrorCode ec = unzip.openArchive(filename);

        if( ec != UnZip::Ok )
            return QByteArray();

        QStringList filesInArchive = unzip.fileList();

        if( filesInArchive.count() > 0 )
        {
            if( filesInArchive.at(0).contains(QString(".fb2")) )
            {
                filename = filesInArchive.at(0);
                ec = unzip.extractFile(filename, QDir::tempPath());
                if( ec == UnZip::Ok )
                {
                    filename = QDir::tempPath()+QString("/")+filename;
                    unzip.closeArchive();
                }
            }
            else
            {
                return QByteArray();
            }
        }
    }


    QDomDocument doc("fb2");
    //QFile f("/home/sa/bookc/test.fb2");
    QFile f(filename);
    if(!f.open(QIODevice::ReadOnly))
        return QByteArray();
    if(!doc.setContent(&f))
    {
            f.close();
            return QByteArray();
    }
    f.close();

    const QDomElement docElement = doc.documentElement();

    QDomElement element = docElement.firstChildElement();
    while( !element.isNull() )
    {
        if( element.tagName() == QLatin1String( "binary" ) )
        {
            QDomElement childCoverpage = element.firstChildElement();
            QString binaryId = element.attribute( "id" );
//            QString binaryId = childCoverpage.attribute( "id" );
            if( binaryId == id )
            {
                const QDomText text = element.firstChild().toText();
                QByteArray data = text.data().toLatin1();
                data = QByteArray::fromBase64( data );

                return data;
            }
        }
        element = element.nextSiblingElement();
    }

    return QByteArray();

}
