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
#ifndef LIBRARY_H
#define LIBRARY_H

#include <QDialog>
#include <QHash>
#include <QList>
#include <QTreeWidget>
#include <QPixmap>

namespace Ui {
    class Library;
}

class Library : public QDialog
{
    Q_OBJECT

public:
    explicit Library(QWidget *parent = 0);
    ~Library();

    QHash<QString, QString> bookNames;
    QHash<QString, QString> bookExtensions;
    QHash<QString, QString> bookAuthors;
    QHash<QString, QString> bookFilenames;
    QHash<QString, QString> bookLangs;
    QHash<QString, QString> bookCoverpages;
    QString currentBookFilename;
    QStringList libraryDirs;

private slots:
    void on_butRefreshLibrary_clicked();

    void on_treeBookLibrary_itemClicked(QTreeWidgetItem *item, int column);

    void on_butLoadBook_clicked();

    void on_butClose_clicked();

private:
    Ui::Library *ui;
    QStringList loadFB2FileInfo(QString filename);
    void writeLibrary();
    void readLibrary();
    void showLibrary();
    QByteArray loadFB2Coverpage(QString id, QString filename);
//    QStringList loadFB2Description(QString filename);
};

#endif // LIBRARY_H
