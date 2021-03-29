/*
*/

#ifndef ErrorFlags_h
#define ErrorFlags_h

#include <iostream>

#include <ArrayDefs.h>

#include <QStringList>

class ErrorFlags
{
public:
    ErrorFlags(int num);
    virtual ~ErrorFlags();
    virtual void setError (int index);
    virtual void clear();
    bool isOk() const;
    bool isSet (int index) const;

    virtual void write (std::ostream& os) const;
    virtual void read (std::istream& is);

    friend std::ostream& operator<< (std::ostream&, const ErrorFlags&);
    friend std::istream& operator>> (std::istream&, ErrorFlags&);

protected:
    QList<bool> errors;

};

#endif
