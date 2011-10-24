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
#ifndef BOOKSETTINGS_H
#define BOOKSETTINGS_H

#include <QDialog>
#include "readerutils.h"
#include <QListWidgetItem>

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
    void on_butParagraphColor_clicked();
    void on_butBgColorFrom_clicked();
    void on_butBgColorTo_clicked();
    void on_cbTitleInUppercase_toggled(bool checked);
    void on_cbHyphsIsOn_toggled(bool checked);
    void on_cbMoveBigImages_toggled(bool checked);
    void on_sbColumnsNum_editingFinished();
    void on_sbIndentValue_editingFinished();
    void on_sbRotateValue_editingFinished();
    void on_sbParagraphLineSpacing_editingFinished();
    void on_butAddLibraryDir_clicked();
    void on_butRemoveLibraryDir_clicked();
    void on_butClearLibraryDirs_clicked();
    void on_chkSetColor_toggled(bool checked);
    void on_chkSetPattern_toggled(bool checked);
    void on_BookSettings_finished(int result);
    void on_buttonBox_accepted();
};

#endif // BOOKSETTINGS_H
