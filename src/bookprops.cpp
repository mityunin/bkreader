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
