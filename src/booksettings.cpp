#include "booksettings.h"
#include "ui_booksettings.h"
#include <QSettings>

BookSettings::BookSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BookSettings)
{
    ui->setupUi(this);
}

void BookSettings::loadSettings()
{
    QSettings settings("MyReader", "MyReader");

    this->ui->editParagraphFont->setText( settings.value( "fonts/paragraphFontFamily" ).toString() + " " + settings.value( "fonts/paragraphPointSize" ).toString() );
    this->ui->editTitleFont->setText( settings.value( "fonts/titleFontFamily" ).toString() + " " + settings.value( "fonts/titlePointSize" ).toString() );
    this->ui->editSubtitleFont->setText( settings.value( "fonts/subtitleFontFamily" ).toString() + " " + settings.value( "fonts/subtitlePointSize" ).toString() );
    this->ui->editCiteFont->setText( settings.value( "fonts/citeFontFamily" ).toString() + " " + settings.value( "fonts/citePointSize" ).toString() );
    this->ui->editPoemFont->setText( settings.value( "fonts/poemFontFamily" ).toString() + " " + settings.value( "fonts/poemPointSize" ).toString() );
    this->ui->editFootnoteFont->setText( settings.value( "fonts/footnoteFontFamily" ).toString() + " " + settings.value( "fonts/footnotePointSize" ).toString() );
    this->ui->editIndicatorFont->setText( settings.value( "fonts/indicatorFontFamily" ).toString() + " " + settings.value( "fonts/indicatorPointSize" ).toString() );
    this->ui->editEpigraphFont->setText( settings.value( "fonts/epigraphFontFamily" ).toString() + " " + settings.value( "fonts/epigraphPointSize" ).toString() );

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
