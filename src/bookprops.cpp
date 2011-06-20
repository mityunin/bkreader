#include "bookprops.h"

BookProps::BookProps()
{
    QFont paragraphFont;
    QFont titleFont;
    QFont subtitleFont;
    QFont citeFont;
    QFont poemFont;
    QFont footnoteFont;
    QFont indicatorFont;

    this->fonts[ QString("paragraph") ] = paragraphFont;
    this->fonts[ QString("title") ] = titleFont;
    this->fonts[ QString("subtitle") ] = subtitleFont;
    this->fonts[ QString("cite") ] = citeFont;
    this->fonts[ QString("poem") ] = poemFont;
    this->fonts[ QString("footnote") ] = footnoteFont;
    this->fonts[ QString("indicator") ] = indicatorFont;

    this->fonts[ "paragraph" ].setFamily("Droid Sans");
    this->fonts[ "paragraph" ].setPointSize(12);
    this->fonts[ "title" ] = this->fonts[ "paragraph" ];
    this->fonts[ "subtitle" ] = this->fonts[ "paragraph" ];
    this->fonts[ "cite" ] = this->fonts[ "paragraph" ];
    this->fonts[ "poem" ] = this->fonts[ "paragraph" ];
    this->fonts[ "footnote" ] = this->fonts[ "paragraph" ];
    this->fonts[ "indicator" ] = this->fonts[ "paragraph" ];
}
