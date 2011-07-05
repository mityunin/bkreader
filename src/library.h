#ifndef LIBRARY_H
#define LIBRARY_H

#include <QDialog>
#include <QHash>
#include <QList>
#include <QTreeWidget>

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
    QString currentBookFilename;

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
//    QStringList loadFB2Description(QString filename);
};

#endif // LIBRARY_H
