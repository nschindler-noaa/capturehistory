#ifndef ArrayDefs_H
#define ArrayDefs_H

#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <list>
#include <algorithm>

#include "Matrix.h"

namespace cbr {

    typedef QList<bool> BoolVector;
    typedef QList<int> IntVector;
    typedef QList<double> DoubleVector;
//    typedef std::vector<std::string> StringVector;
    typedef QList<std::string> StringList;
    typedef Matrix<int> IntMatrix;
    typedef Matrix<double> DoubleMatrix;

    template <class Type>
    std::ostream& operator<<(std::ostream& os, const std::vector<Type> vector) {
        for (size_t i = 0; i < vector.size(); ++i)
            os << vector[i] << " ";
        return os;
    }

    template <class Type>
    std::ostream& operator<<(std::ostream& os, const QList<Type> list) {
        for (int i = 0; i < list.count(); ++i)
            os << list[i] << " ";
        return os;
    }

    template <class Type>
    std::ostream& operator<<(std::ostringstream& os, const std::vector<Type> vector) {
        for (size_t i = 0; i < vector.size(); ++i)
            os << vector[i] << " ";
        return os;
    }

    template <class Type>
    std::ostream& operator<<(std::ostringstream& os, const QList<Type> list) {
        for (int i = 0; i < list.count(); ++i)
            os << list[i] << " ";
        return os;
    }

/*    template <class Type>
    static void sortUnique(Type& list) {
        if (list.size() < 2)
            return;

        std::sort(list.begin(), list.end());
        typename Type::iterator it1 = list.begin();
        typename Type::iterator it0;

        it0 = it1;
        ++it1;
        while (it1 != list.end()) {
            if (*it0 == *it1)
                list.erase(it0);
            it0 = it1;
            ++it1;
        }
    }*/

};




#endif
