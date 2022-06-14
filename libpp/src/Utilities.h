/*
 * Utilities.h
 */

#ifndef Utilities_h
#define Utilities_h

#include <QStringList>

class Utilities {
public:
    static void sortUnique( QStringList& list ) {
        if ( list.size() < 2 )
            return;

        list.sort();
    }

};

#endif
