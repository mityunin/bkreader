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
	
public slots:
	void openFile();
	void setFontBigger();
	void setFontSmaller();
	void setLinesBigger();
	void setLinesSmaller();
        void showTime();
        void openBookSlot();
        void openSettingsWindow();
        void openLibrarySlot();
//        void setAntialias();
};
#endif
