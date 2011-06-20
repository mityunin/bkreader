#ifndef HYPHENATOR_H
#define HYPHENATOR_H
#include <QtCore>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QHash>
#include <QtGui/QFont>

class hyphenator
{
public:
    hyphenator();
    void loadHyphPatterns(QString lang);
    QStringList hyphenateWord(QString word);

    QHash<QString, QHash<int, int> > pats;
};

#endif // HYPHENATOR_H
