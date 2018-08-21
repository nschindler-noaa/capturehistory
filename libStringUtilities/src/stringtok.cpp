#include "StringTok.h"

#include <QStringList>
#include <QChar>

/*

void stringTok (QStringList &container, const QString &in, const char* const delimiters)
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
*/
