/*
 * Same as stringtok_h.txt, but doesn't (visably) use C functions.
*/

#ifndef StringTok_h
#define StringTok_h

#include <string>
#include <QString>
#include <QStringList>

// The std:: prefix is not used here, for readability, and a line like
// "using namespace std;" is dangerous to have in a header file.


//template <typename Container>
inline
void stringTok( QStringList &container, const QString &in, const char* const delimiters = " \t\n" )
{
    QString dels (delimiters);
    QStringList tokens;
    QStringList allTokens(in);

    for (int d = 0; d < dels.count(); d++)
    {
        QChar dl = dels.at(d);

        for (int i = 0; i < allTokens.count(); i++)
        {
            tokens.append(allTokens.at(i).split(dl, QString::SkipEmptyParts));
        }
        allTokens = tokens;
        tokens.clear();
    }
    container.append(allTokens);
}

/*    const std::string::size_type len = in.length();
    std::string::size_type i = 0;
    
    while ( i < len )
    {
        // eat leading whitespace
        i = in.find_first_not_of (delimiters, i);
        if (i == std::string::npos)
            return;   // nothing left but white space
        
        // find the end of the token
       std::string::size_type j = in.find_first_of (delimiters, i);
        
        // push token
        if (j == std::string::npos) {
            container.push_back (in.substr(i));
            return;
        } else
            container.push_back (in.substr(i, j-i));
        
        // set up for next loop
        i = j + 1;
    }
}*/


#endif
