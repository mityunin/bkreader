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
        prefMenu.addAction("Fonts +");
        prefMenu.addAction("Fonts -");
        prefMenu.addAction("Linespacing +");
        prefMenu.addAction("Linespacing -");
        prefMenu.addSeparator();
//        prefMenu.addAction("Settings");
        QAction *openSettingsAction = new QAction(("Settings"), win);
        prefMenu.addAction(openSettingsAction);

        win->connect(openSettingsAction, SIGNAL(triggered()), &tmplt, SLOT(openSettingsWindow()));


        win->menuBar()->addMenu(&fileMenu);
        win->menuBar()->addMenu(&prefMenu);
//        win->menuBar()-> addMenu("File")->addSeparator();
//        win->menuBar()->addMenu("Settings")->addAction("Preferences");
	win->setCentralWidget(&tmplt);
        tmplt.menuBar = win->menuBar();
	win->resize(640, 480);
	//b->loadFB2();
	win->show(); 
	app.connect( &app, SIGNAL( lastWindowClosed() ), &app, SLOT( quit() ) );
	return app.exec();
}
