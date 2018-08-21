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

    typedef std::vector<int> IntVector;
    typedef std::vector<double> DoubleVector;
    typedef std::vector<std::string> StringVector;
    typedef std::list<std::string> StringList;
    typedef std::vector<bool> BoolVector;
    typedef Matrix<int> IntMatrix;
    typedef Matrix<double> DoubleMatrix;
    typedef std::vector<bool> BoolVector;

    template <class Type>
    std::ostream& operator<<(std::ostream& os, const std::vector<Type> vector) {
        for (size_t i = 0; i < vector.size(); ++i)
            os << vector[i] << " ";
        return os;
    }

    template <class Type>
    std::ostream& operator<<(std::ostringstream& os, const std::vector<Type> vector) {
        for (size_t i = 0; i < vector.size(); ++i)
            os << vector[i] << " ";
        return os;
    }

    template <class Type>
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
    }

};




#endif
