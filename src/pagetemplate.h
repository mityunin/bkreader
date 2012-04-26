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
#ifndef PAGETEMPLATE_H
#define PAGETEMPLATE_H
#include <QtGui>
#include <QtCore>
#include <QWidget>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QFile>
#include <QtGui/QFont>
//#include <QBool>
//#include <QTime>
#include "pageline.h"
#include "book.h"
#include "booksettings.h"
#include "library.h"

//
class PageTemplate: public QWidget
{
	Q_OBJECT
public:
	PageTemplate(QWidget *parent=0);
	void drawLayout(QList<PageLine> page, int columnNum);
	QList<PageLine> getPage(int i);
	void setBook(book *b);
	
	book *b;
        QTextLayout layout;
        QMenuBar *menuBar;
        QMenu *contentsMenu;
        QTimer *mouseTimer;
        QApplication *app;
//        QTimer      bookTimer;
//        QTime       bookTime;

protected:
	void paintEvent(QPaintEvent *event);
	void resizeEvent(QResizeEvent *event);
        void keyPressEvent(QKeyEvent *event);

private:
        QString currentTitle;
        QPixmap widgetPixmap;
        void preparePaintEvent();
        void makeContentsMenu();
        void mouseMoveEvent(QMouseEvent *e);
	
public slots:
	void openFile();
	void setFontBigger();
	void setFontSmaller();
	void setLinesBigger();
	void setLinesSmaller();
        void setHideMenu();
        void showTime();
        void openBookSlot();
        void openSettingsWindow();
        void openLibrarySlot();
        void openChapterSlot();
//        void setAntialias();
        void hideMousePointer();
};
#endif
