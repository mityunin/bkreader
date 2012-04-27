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
#include "mainwindowimpl.h"
//
MainWindowImpl::MainWindowImpl( QWidget * parent, Qt::WFlags f) 
	: QMainWindow(parent, f)
{
        //setupUi(this);
//        app->installEventFilter(this);
//        qDebug()<<QString("constr");
    this->mouseTimer = new QTimer();
    connect(mouseTimer, SIGNAL(timeout()), this, SLOT(hideMousePointer()) );
    mouseTimer->start(5000);
}

bool MainWindowImpl::eventFilter(QObject *obj, QEvent *event)
{
    if( event->type() == QEvent::MouseMove )
    {
        app->setOverrideCursor( QCursor(Qt::ArrowCursor) );
        mouseTimer->start(5000);
        return true;
    }
    //qDebug()<<event;
    return QMainWindow::eventFilter(obj, event);
}

void MainWindowImpl::hideMousePointer()
{
    app->setOverrideCursor( QCursor(Qt::BlankCursor) );
    mouseTimer->stop();
}

//
