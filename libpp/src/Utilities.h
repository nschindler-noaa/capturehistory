/*
 * Utilities.h
 */

#ifndef Utilities_h
#define Utilities_h

#include <QStringList>

class Utilities {
public:
    static void sortUnique(QStringList& list) {
        list.sort();
#if 0
        if (list.size() < 2)
            return;

        list.sort();
        QStringList::iterator it1 = list.begin();
        QStringList::iterator it0;

        it0 = it1;
        ++it1;

        QStringList::iterator it_end = list.end();
        while ( it1 != it_end ) {
            const QString& s0 = *it0;
            const QString& s1 = *it1;
            if (*it0 == *it1)
                list.erase(it0);
            it0 = it1;
            ++it1;
        }

#endif
    }

};

#endif
