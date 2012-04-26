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
#include <QApplication>
#include <QMainWindow>
#include "mainwindowimpl.h"
#include "book.h"
#include "pagetemplate.h"
//
int main(int argc, char ** argv)
{
	QApplication app( argc, argv );
	//MainWindowImpl win;
	QMainWindow *win = new QMainWindow(0, Qt::Window);
        PageTemplate tmplt;// = new PageTemplate;
        tmplt.app = &app;
        book b;// = new book();
        tmplt.setBook(&b);

        QMenu fileMenu("File");

        QAction *openBookAction = new QAction(("Open book"), win);
        QAction *openLibraryAction = new QAction(("Library"), win);
        fileMenu.addAction(openBookAction);
        fileMenu.addAction(openLibraryAction);
//        fileMenu.addAction("Open book", )
        fileMenu.addSeparator();
        fileMenu.addAction("Quit");

        win->connect(openBookAction, SIGNAL(triggered()), &tmplt, SLOT(openBookSlot()));
        win->connect(openLibraryAction, SIGNAL(triggered()), &tmplt, SLOT(openLibrarySlot()));

        QMenu prefMenu("Settings");
//        prefMenu.addAction("Fonts +");
//        prefMenu.addAction("Fonts -");
//        prefMenu.addAction("Linespacing +");
//        prefMenu.addAction("Linespacing -");
//        prefMenu.addSeparator();
//        prefMenu.addAction("Settings");
        QAction *openSettingsAction = new QAction(("Settings"), win);
        prefMenu.addAction(openSettingsAction);

        win->connect(openSettingsAction, SIGNAL(triggered()), &tmplt, SLOT(openSettingsWindow()));

        QMenu contentsMenu("Contents");



        win->menuBar()->addMenu(&fileMenu);
        win->menuBar()->addMenu(&prefMenu);
        win->menuBar()->addMenu(&contentsMenu);
//        win->menuBar()-> addMenu("File")->addSeparator();
//        win->menuBar()->addMenu("Settings")->addAction("Preferences");
	win->setCentralWidget(&tmplt);
        tmplt.menuBar = win->menuBar();
        tmplt.contentsMenu = &contentsMenu;
	win->resize(640, 480);
	//b->loadFB2();
	win->show(); 
	app.connect( &app, SIGNAL( lastWindowClosed() ), &app, SLOT( quit() ) );
	return app.exec();
}
