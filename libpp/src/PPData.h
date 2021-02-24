/*
*
*/

#ifndef PPData_h
#define PPData_h

#include <string>
#include <map>

#include <QStringList>
#include <QDateTime>

#include <ArrayDefs.h>

class PPData
{
public:
    PPData(int numFields);
    virtual ~PPData() {}
    bool isHeader() const { return header; }
    bool isOk() const { return ok; }
    static bool isValidPitTag(const QString pitTag);
    bool isValidDate(const QString s);
    bool isValidTime(const QString s);
    bool isValidDateTime(const QString s);
    double getTimeFromDate(const QString s);
    QDateTime getDateTime(const QString s);

    virtual bool read(std::istream& is) = 0;
    virtual bool parseColumnData() = 0;
    virtual void write(std::ostream& os) const = 0;

    static void replaceMissingFields (QString s);

    friend std::istream& operator>> (std::istream& is, PPData& d);
    friend std::ostream& operator<< (std::ostream& os, const PPData& d);

    void setColumnOrder(int key, int value) { columnOrder[key] = value; }

protected:
    static bool firstDate;
    static QString NullString;
    std::map<int, unsigned int> columnOrder;
    QStringList columnNames;
    QStringList columnData;
    int numFields;
    bool header;
    bool indata;
    bool ok;

    virtual void resetColumnOrder();

    QStringList validDateFormats;
    QStringList validTimeFormats;
};

#endif

