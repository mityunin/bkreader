#include "hyphenator.h"
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QHash>
#include <QtCore/QFile>
#include <QtCore/QDir>
#include <QtCore/QTextStream>
#include <QtCore/QVector>

hyphenator::hyphenator()
{


}

void hyphenator::loadHyphPatterns(QString lang)
{
    if(this->pats.size()>0) return;

//    this->pats.clear();
    QString filename = QDir::currentPath() + QString("/patterns/hyph-ru.pat.txt");
//    qDebug() << filename;
    QStringList pats;
    QFile f(filename);
    f.open(QIODevice::ReadOnly);
    QTextStream in(&f);
    in.setCodec("UTF-8");
    if( f.exists() )
    {
        while(!in.atEnd())
        {
            QString line = in.readLine();
            QHash<int, int> t;
            QString str;
            int index=0;
            for(int i=0;i<line.size();i++)
            {
                if( line[i].isDigit() )
                {
                    t[index] = line[i].digitValue();
                }
                else
                {
                    str.append(line[i]);
                    index++;
                }
            }
            this->pats[str]=t;
        }
    }
    f.close();
}

QStringList hyphenator::hyphenateWord(QString word)
{
    if(word.size() < 4) return QStringList();

    word.remove(QLatin1String("."), Qt::CaseInsensitive);
    word.remove(QLatin1String(","), Qt::CaseInsensitive);
    word.remove(QLatin1String(":"), Qt::CaseInsensitive);


    QString w;
//    w.remove(QChar(""), Qt::CaseInsensitive);
    w = word.toLower().prepend(".").append(".");

    QVector<int> hyph_vector;
    hyph_vector.fill(0, w.size());

    for(int l_letter=0;l_letter<w.size();l_letter++)
    {
        for(int f_letter=0;f_letter<l_letter;f_letter++)
        {
            if(this->pats.contains(w.mid(f_letter, l_letter-f_letter)))
            {
                QHash<int, int> tmp_pattern;
                tmp_pattern = this->pats[w.mid(f_letter, l_letter-f_letter)];

                foreach(int k, tmp_pattern.keys())
                {
                    if(hyph_vector[f_letter+k]<tmp_pattern[k])
                        hyph_vector[f_letter+k]=tmp_pattern[k];
                }
            }
        }
    }

    QStringList ret_list;
//    qDebug()<<hyph_vector;

    if(hyph_vector.size()>0)
    {
        for(int i=3;i<w.size()-2;i++)
        {
            if(hyph_vector[i]%2)
            {
                ret_list.append(word.left(i-1));
            }
        }
//        qDebug()<<ret_list;
    }

    return ret_list;
}
