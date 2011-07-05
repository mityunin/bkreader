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

    QDirIterator dir_iterator(QString( "/home/sa/Downloads" ), fileFilters, QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories );
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
        }
        else if( dir_iterator.fileInfo().suffix() == QLatin1String("txt") )
        {
            this->bookNames[dir_iterator.fileInfo().absoluteFilePath()] = dir_iterator.fileName();
            this->bookAuthors[dir_iterator.fileInfo().absoluteFilePath()] = QString("");
            this->bookLangs[dir_iterator.fileInfo().absoluteFilePath()] = QString("");
            this->bookExtensions[dir_iterator.fileInfo().absoluteFilePath()] = QString("txt");
            this->bookFilenames[dir_iterator.fileInfo().absoluteFilePath()] = dir_iterator.fileInfo().absoluteFilePath();
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
    QStringList fb2info; //0 - bookName, 1 - bookAuthor, 2 - lang
    fb2info.append("Unknown");
    fb2info.append("Unknown");
    fb2info.append("ru");

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

    this->ui->labBookAuthor->setText(bookAuthor);
    this->ui->labBookName->setText(bookName);
    this->ui->labBookExtension->setText(bookExtension);
    this->ui->labBookLang->setText(bookLang);
    this->ui->labFilename->setText(bookFilename);

    if( !bookFilename.isEmpty() )
        this->currentBookFilename = bookFilename;
    else
        this->currentBookFilename.clear();
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
