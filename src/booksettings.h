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

private slots:
    void on_butParagraphFont_clicked();
    void on_butTitleFont_clicked();
    void on_butSubtitleFont_clicked();
    void on_butPoemFont_clicked();
    void on_butCiteFont_clicked();
    void on_butFootnoteFont_clicked();
    void on_butIndicatorFont_clicked();
    void on_butEpigraphFont_clicked();
    void on_sbLeftMargin_editingFinished();
    void on_sbRightMargin_editingFinished();
    void on_sbTopMargin_editingFinished();
    void on_sbBottomMargin_editingFinished();
    void on_sbCiteMargin_editingFinished();
    void on_sbPoemMargin_editingFinished();
    void on_sbEpigraphMargin_editingFinished();
};

#endif // BOOKSETTINGS_H
