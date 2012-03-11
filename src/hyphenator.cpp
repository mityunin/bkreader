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
    QString hyphPath = lang;
    hyphPath.remove(".");
    hyphPath.remove("\\");

//    QString filename = QDir::currentPath() + QString("/patterns/hyph-ru.pat.txt");
    QString localPatterns = QDir::homePath()+QString("/.config/bkreader/patterns/");
    QString sharePatterns = QString("/usr/share/bkreader/patterns");

    QDir shareDir;
    QDir localPatternsDir;

    shareDir.setCurrent(sharePatterns);
    localPatternsDir.setCurrent(localPatterns);

    bool shareDirExitsts = shareDir.exists(sharePatterns);
    bool localPatternsDirExists = localPatternsDir.exists(localPatterns);

    if( shareDirExitsts && !localPatternsDirExists )
    {
        localPatternsDir.mkpath(localPatterns);
        foreach( QString patternFile, shareDir.entryList() )
        {
            QFile::copy(patternFile, localPatterns+patternFile );
        }
    }

    QString filename = QDir::homePath()+QString("/.config/bkreader/patterns/hyph-")+hyphPath+QString(".pat.txt");

//    QString filename = QString("/usr/share/bkreader/patterns/hyph-")+hyphPath+QString(".pat.txt");
//    QString filename = QDir::currentPath() + QString("/patterns/hyph-")+hyphPath+QString(".pat.txt");

    QStringList pats;
    QFile f(filename);
    if( !f.exists() )
        f.setFileName( QString("patterns/hyph-")+hyphPath+QString(".pat.txt") );

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

//    word.remove(QLatin1String("."), Qt::CaseInsensitive);
//    word.remove(QLatin1String(","), Qt::CaseInsensitive);
//    word.remove(QLatin1String(":"), Qt::CaseInsensitive);

//    remove special characters
    word.replace(QChar(0x002e), "");
    word.replace(QChar(0x0021), "");
    word.replace(QChar(0x003a), "");
    word.replace(QChar(0x003b), "");
//    remove "hyphen" and "minus" to the end of line
    word.remove( word.indexOf(QChar(0x002d)), word.length() );
    word.remove( word.indexOf(QChar(0x207b)), word.length() );
    word.remove( word.indexOf(QChar(0x208b)), word.length() );
    word.remove( word.indexOf(QChar(0xfe63)), word.length() );
    word.remove( word.indexOf(QChar(0xff0d)), word.length() );
    word.remove( word.indexOf(QChar(0xe002d)), word.length() );

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
