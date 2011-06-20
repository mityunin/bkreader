#ifndef BOOKSETTINGS_H
#define BOOKSETTINGS_H

#include <QDialog>
#include "readerutils.h"

namespace Ui {
    class BookSettings;
}

class BookSettings : public QDialog
{
    Q_OBJECT

public:
    explicit BookSettings(QWidget *parent = 0);
    ~BookSettings();

    ReaderUtils *utils;
    void loadSettings();
    void saveSettings();

private:
    Ui::BookSettings *ui;
};

#endif // BOOKSETTINGS_H
