#ifndef BOOKPROPS_H
#define BOOKPROPS_H
#include <QtGui>
#include <QtCore>
#include <QFont>

class BookProps
{
public:
    BookProps();

    QHash<QString, QFont> fonts;
};

#endif // BOOKPROPS_H
