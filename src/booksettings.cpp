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
#include "booksettings.h"
#include "ui_booksettings.h"
#include <QSettings>
#include <QFontDialog>
#include <QColorDialog>
#include <QFileDialog>

BookSettings::BookSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BookSettings)
{
    ui->setupUi(this);
}

void BookSettings::loadSettings()
{
    this->ui->editParagraphFont->setText( this->utils->paragraphFont.family() );
    this->ui->editTitleFont->setText( this->utils->titleFont.family() );
    this->ui->editSubtitleFont->setText( this->utils->subtitleFont.family() );
    this->ui->editCiteFont->setText( this->utils->citeFont.family() );
    this->ui->editPoemFont->setText( this->utils->poemFont.family() );
    this->ui->editFootnoteFont->setText( this->utils->footnoteFont.family() );
    this->ui->editIndicatorFont->setText( this->utils->indicatorFont.family() );
    this->ui->editEpigraphFont->setText( this->utils->epigraphFont.family() );

    this->ui->sbLeftMargin->setValue( this->utils->leftMargin );
    this->ui->sbRightMargin->setValue( this->utils->rightMargin );
    this->ui->sbBottomMargin->setValue( this->utils->bottomMargin );
    this->ui->sbTopMargin->setValue( this->utils->topMargin );
    this->ui->sbCiteMargin->setValue( this->utils->citeMargin );
    this->ui->sbEpigraphMargin->setValue( this->utils->epigraphMargin );
    this->ui->sbPoemMargin->setValue( this->utils->poemMargin );

    this->ui->editParagraphColor->setText( this->utils->paracolor );
    this->ui->editBgColorFrom->setText( this->utils->bgColorFrom );
    this->ui->editBgColorTo->setText( this->utils->bgColorTo );

    this->ui->cbTitleInUppercase->setChecked( this->utils->isTitleInUpperCase );
    this->ui->cbHyphsIsOn->setChecked( this->utils->hyphsIsOn );
    this->ui->cbMoveBigImages->setChecked( this->utils->moveBigImages );

    this->ui->sbIndentValue->setValue( this->utils->indentValue );
    this->ui->sbColumnsNum->setValue( this->utils->columnsNum );
    this->ui->sbRotateValue->setValue( this->utils->rotateValue );

    this->ui->sbParagraphLineSpacing->setValue( this->utils->paragraphLineSpacing );

    this->ui->listLibraryDirs->clear();
    foreach( QString libraryDir, this->utils->libraryDirs )
    {
        QListWidgetItem *item = new QListWidgetItem();
        item->setText(libraryDir);
        this->ui->listLibraryDirs->addItem(item);
    }

//    QSettings settings("MyReader", "MyReader");

//    this->ui->editParagraphFont->setText( settings.value( "fonts/paragraphFontFamily" ).toString() + " " + settings.value( "fonts/paragraphPointSize" ).toString() );
//    this->ui->editTitleFont->setText( settings.value( "fonts/titleFontFamily" ).toString() + " " + settings.value( "fonts/titlePointSize" ).toString() );
//    this->ui->editSubtitleFont->setText( settings.value( "fonts/subtitleFontFamily" ).toString() + " " + settings.value( "fonts/subtitlePointSize" ).toString() );
//    this->ui->editCiteFont->setText( settings.value( "fonts/citeFontFamily" ).toString() + " " + settings.value( "fonts/citePointSize" ).toString() );
//    this->ui->editPoemFont->setText( settings.value( "fonts/poemFontFamily" ).toString() + " " + settings.value( "fonts/poemPointSize" ).toString() );
//    this->ui->editFootnoteFont->setText( settings.value( "fonts/footnoteFontFamily" ).toString() + " " + settings.value( "fonts/footnotePointSize" ).toString() );
//    this->ui->editIndicatorFont->setText( settings.value( "fonts/indicatorFontFamily" ).toString() + " " + settings.value( "fonts/indicatorPointSize" ).toString() );
//    this->ui->editEpigraphFont->setText( settings.value( "fonts/epigraphFontFamily" ).toString() + " " + settings.value( "fonts/epigraphPointSize" ).toString() );

//    this->paragraphFont.setFamily( settings.value( "fonts/paragraphFontFamily" ).toString() );
//    this->paragraphFont.setPointSize( settings.value( "fonts/paragraphPointSize" ).toInt() );
//    this->paragraphFont.setItalic( settings.value( "fonts/paragraphItalic" ).toBool() );
//    this->paragraphFont.setBold( settings.value( "fonts/paragraphBold" ).toBool() );
//    this->paragraphFont.setUnderline( settings.value( "fonts/paragraphUnderline" ).toBool() );
//    this->paragraphLineSpacing = settings.value( "fonts/paragraphLineSpacing" ).toFloat();

//    this->titleFont.setFamily( settings.value( "fonts/titleFontFamily").toString() );
//    this->titleFont.setPointSize( settings.value( "fonts/titlePointSize" ).toInt() );
//    this->titleFont.setItalic( settings.value( "fonts/titleItalic" ).toBool() );
//    this->titleFont.setBold( settings.value( "fonts/titleBold" ).toBool() );
//    this->titleFont.setUnderline( settings.value( "fonts/titleUnderline").toBool() );

//    this->subtitleFont.setFamily( settings.value( "fonts/subtitleFontFamily" ).toString() );
//    this->subtitleFont.setPointSize( settings.value( "fonts/subtitlePointSize" ).toInt() );
//    this->subtitleFont.setItalic( settings.value( "fonts/subtitleItalic" ).toBool() );
//    this->subtitleFont.setBold( settings.value( "fonts/subtitleBold" ).toBool() );
//    this->subtitleFont.setUnderline( settings.value( "fonts/subtitleUnderline" ).toBool() );

//    this->citeFont.setFamily( settings.value( "fonts/citeFontFamily" ).toString() );
//    this->citeFont.setPointSize( settings.value( "fonts/citePointSize" ).toInt() );
//    this->citeFont.setItalic( settings.value( "fonts/citeItalic" ).toBool() );
//    this->citeFont.setBold( settings.value( "fonts/citeBold" ).toBool() );
//    this->citeFont.setUnderline( settings.value( "fonts/citeUnderline" ).toBool() );

//    this->footnoteFont.setFamily( settings.value( "fonts/footnoteFontFamily" ).toString() );
//    this->footnoteFont.setPointSize( settings.value( "fonts/footnotePointSize" ).toInt() );
//    this->footnoteFont.setItalic( settings.value( "fonts/footnoteItalic" ).toBool() );
//    this->footnoteFont.setBold( settings.value( "fonts/footnoteBold" ).toBool() );
//    this->footnoteFont.setUnderline( settings.value( "fonts/footnoteUnderline" ).toBool() );

//    this->poemFont.setFamily( settings.value( "fonts/poemFontFamily" ).toString() );
//    this->poemFont.setPointSize( settings.value( "fonts/poemPointSize" ).toInt() );
//    this->poemFont.setItalic( settings.value( "fonts/poemItalic" ).toBool() );
//    this->poemFont.setBold( settings.value( "fonts/poemBold" ).toBool() );
//    this->poemFont.setUnderline( settings.value( "fonts/poemUnderline" ).toBool() );

//    this->indicatorFont.setFamily( settings.value( "fonts/indicatorFontFamily" ).toString() );
//    this->indicatorFont.setPointSize( settings.value( "fonts/indicatorPointSize" ).toInt() );
//    this->indicatorFont.setItalic( settings.value( "fonts/indicatorItalic" ).toBool() );
//    this->indicatorFont.setBold( settings.value( "fonts/indicatorBold" ).toBool() );
//    this->indicatorFont.setUnderline( settings.value( "fonts/indicatorUnderline" ).toBool() );

//    this->epigraphFont.setFamily( settings.value( "fonts/epigraphFontFamily" ).toString() );
//    this->epigraphFont.setPointSize( settings.value( "fonts/epigraphPointSize" ).toInt() );
//    this->epigraphFont.setItalic( settings.value( "fonts/epigraphItalic" ).toBool() );
//    this->epigraphFont.setBold( settings.value( "fonts/epigraphBold" ).toBool() );
//    this->epigraphFont.setUnderline( settings.value( "fonts/epigraphUnderline" ).toBool() );

//    this->isTitleInUpperCase = settings.value( "read/titleIsUppercase").toBool();
//    this->hyphsIsOn = settings.value( "read/hyphsIsOn" ).toBool();
//    this->columnsNum = settings.value( "read/columnsNum" ).toInt();
//    this->rotateValue = settings.value( "read/rotateValue" ).toInt();
//    this->indentValue = settings.value( "read/indentValue").toInt();

//    this->leftMargin = settings.value( "margins/leftMargin" ).toInt();
//    this->rightMargin = settings.value( "margins/rightMargin" ).toInt();
//    this->topMargin = settings.value( "margins/topMargin" ).toInt();
//    this->bottomMargin = settings.value( "margins/bottomMargin" ).toInt();
//    this->citeMargin = settings.value( "margins/citeMargin" ).toInt();
//    this->poemMargin = settings.value( "margins/poemMargin" ).toInt();
//    this->epigraphMargin = settings.value( "margins/epigraphMargin" ).toInt();
}

BookSettings::~BookSettings()
{
    delete ui;
}

void BookSettings::on_butParagraphFont_clicked()
{
    bool ok;
    QFont font;
    font = QFontDialog::getFont(&ok, this->utils->paragraphFont, this);
    if(ok)
    {
        this->utils->paragraphFont = font;
        this->utils->writeSettings();
        this->loadSettings();
    }
}

void BookSettings::on_butTitleFont_clicked()
{
    bool ok;
    QFont font;
    font = QFontDialog::getFont(&ok, this->utils->titleFont, this);
    if(ok)
    {
        this->utils->titleFont = font;
        this->utils->writeSettings();
        this->loadSettings();
    }
}

void BookSettings::on_butSubtitleFont_clicked()
{
    bool ok;
    QFont font;
    font = QFontDialog::getFont(&ok, this->utils->subtitleFont, this);
    if(ok)
    {
        this->utils->subtitleFont = font;
        this->utils->writeSettings();
        this->loadSettings();
    }
}

void BookSettings::on_butPoemFont_clicked()
{
    bool ok;
    QFont font;
    font = QFontDialog::getFont(&ok, this->utils->poemFont, this);
    if(ok)
    {
        this->utils->poemFont = font;
        this->utils->writeSettings();
        this->loadSettings();
    }
}

void BookSettings::on_butCiteFont_clicked()
{
    bool ok;
    QFont font;
    font = QFontDialog::getFont(&ok, this->utils->citeFont, this);
    if(ok)
    {
        this->utils->citeFont = font;
        this->utils->writeSettings();
        this->loadSettings();
    }
}

void BookSettings::on_butFootnoteFont_clicked()
{
    bool ok;
    QFont font;
    font = QFontDialog::getFont(&ok, this->utils->footnoteFont, this);
    if(ok)
    {
        this->utils->footnoteFont = font;
        this->utils->writeSettings();
        this->loadSettings();
    }
}

void BookSettings::on_butIndicatorFont_clicked()
{
    bool ok;
    QFont font;
    font = QFontDialog::getFont(&ok, this->utils->indicatorFont, this);
    if(ok)
    {
        this->utils->indicatorFont = font;
        this->utils->writeSettings();
        this->loadSettings();
    }
}

void BookSettings::on_butEpigraphFont_clicked()
{
    bool ok;
    QFont font;
    font = QFontDialog::getFont(&ok, this->utils->epigraphFont, this);
    if(ok)
    {
        this->utils->epigraphFont = font;
        this->utils->writeSettings();
        this->loadSettings();
    }
}

void BookSettings::on_sbLeftMargin_editingFinished()
{
    this->utils->leftMargin = this->ui->sbLeftMargin->value();
    this->utils->writeSettings();
    this->loadSettings();
}

void BookSettings::on_sbRightMargin_editingFinished()
{
    this->utils->rightMargin = this->ui->sbRightMargin->value();
    this->utils->writeSettings();
    this->loadSettings();
}

void BookSettings::on_sbTopMargin_editingFinished()
{
    this->utils->topMargin = this->ui->sbTopMargin->value();
    this->utils->writeSettings();
    this->loadSettings();
}

void BookSettings::on_sbBottomMargin_editingFinished()
{
    this->utils->bottomMargin = this->ui->sbBottomMargin->value();
    this->utils->writeSettings();
    this->loadSettings();
}

void BookSettings::on_sbCiteMargin_editingFinished()
{
    this->utils->citeMargin = this->ui->sbCiteMargin->value();
    this->utils->writeSettings();
    this->loadSettings();
}

void BookSettings::on_sbPoemMargin_editingFinished()
{
    this->utils->poemMargin = this->ui->sbPoemMargin->value();
    this->utils->writeSettings();
    this->loadSettings();
}

void BookSettings::on_sbEpigraphMargin_editingFinished()
{
    this->utils->epigraphMargin = this->ui->sbEpigraphMargin->value();
    this->utils->writeSettings();
    this->loadSettings();
}

void BookSettings::on_butParagraphColor_clicked()
{
    QColor color;
    color = QColorDialog::getColor(QColor( QColor(this->utils->paracolor).rgb() ));
    this->utils->paracolor = color.name();
    this->utils->writeSettings();
    this->loadSettings();
}

void BookSettings::on_butBgColorFrom_clicked()
{
    QColor color;
    color = QColorDialog::getColor(QColor( QColor(this->utils->bgColorFrom).rgb() ));
    this->utils->bgColorFrom = color.name();
    this->utils->writeSettings();
    this->loadSettings();
}

void BookSettings::on_butBgColorTo_clicked()
{
    QColor color;
    color = QColorDialog::getColor(QColor( QColor(this->utils->bgColorTo).rgb() ));
    this->utils->bgColorTo = color.name();
    this->utils->writeSettings();
    this->loadSettings();
}

void BookSettings::on_cbTitleInUppercase_toggled(bool checked)
{
    this->utils->isTitleInUpperCase = checked;
    this->utils->writeSettings();
    this->loadSettings();
}

void BookSettings::on_cbHyphsIsOn_toggled(bool checked)
{
    this->utils->hyphsIsOn = checked;
    this->utils->writeSettings();
    this->loadSettings();
}

void BookSettings::on_cbMoveBigImages_toggled(bool checked)
{
    this->utils->moveBigImages = checked;
    this->utils->writeSettings();
    this->loadSettings();
}

void BookSettings::on_sbColumnsNum_editingFinished()
{
    this->utils->columnsNum = this->ui->sbColumnsNum->value();
    this->utils->writeSettings();
    this->loadSettings();
}

void BookSettings::on_sbIndentValue_editingFinished()
{
    this->utils->indentValue = this->ui->sbIndentValue->value();
    this->utils->writeSettings();
    this->loadSettings();
}

void BookSettings::on_sbRotateValue_editingFinished()
{
    this->utils->rotateValue = this->ui->sbRotateValue->value();
    this->utils->writeSettings();
    this->loadSettings();
}

void BookSettings::on_sbParagraphLineSpacing_editingFinished()
{
    this->utils->paragraphLineSpacing = this->ui->sbParagraphLineSpacing->value();
    this->utils->writeSettings();
    this->loadSettings();
}

void BookSettings::on_butAddLibraryDir_clicked()
{
    QString libraryDirPath = QFileDialog::getExistingDirectory();
    if( !libraryDirPath.isEmpty() )
    {
        QListWidgetItem *itemLibraryDir = new QListWidgetItem();
        itemLibraryDir->setText(libraryDirPath);
        this->ui->listLibraryDirs->addItem(itemLibraryDir);
    }

    this->utils->libraryDirs.clear();

    for( int i=0; i<this->ui->listLibraryDirs->count(); i++ )
    {
        this->utils->libraryDirs.append( this->ui->listLibraryDirs->item(i)->text() );
    }

    this->utils->libraryDirs.removeDuplicates();
    this->utils->writeSettings();
}

void BookSettings::on_butRemoveLibraryDir_clicked()
{
    qDeleteAll(this->ui->listLibraryDirs->selectedItems());

    this->utils->libraryDirs.clear();

    for( int i=0; i<this->ui->listLibraryDirs->count(); i++ )
    {
        this->utils->libraryDirs.append( this->ui->listLibraryDirs->item(i)->text() );
    }

    this->utils->libraryDirs.removeDuplicates();
    this->utils->writeSettings();
}

void BookSettings::on_butClearLibraryDirs_clicked()
{
    this->ui->listLibraryDirs->clear();

    this->utils->libraryDirs.clear();
    this->utils->writeSettings();
}
