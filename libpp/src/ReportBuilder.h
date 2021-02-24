#ifndef ReportBuilder_H
#define ReportBuilder_H

// Provides the ability to build and write a text report by placing
// text on a page independent of other text, and in any order,
// regardless of where it lies on the page.

#include <QStringList>
#include "ReportElement.h"
#include <string>
#include <set>
#include <utility>
#include "LogicError.h"
#include "Matrix.h"
#include <iostream>

class ReportBuilder
{
public:
    ReportBuilder() {}
    ~ReportBuilder() {}

    int insertLeft(int row, int col, const QString text);
    int insertLeft(int row, int col, int fieldLength, const QString text);
    int insertLeft(int row, int col, int fieldLength, int fractLength,
        double dVal);
    int insertLeft(int row, int col, int fractLength, double dVal);
    int insertLeft(int row, int col, int fieldLength, int iVal);
    int insertLeft(int row, int col, int iVal);
    int insertLeftExp(int row, int col, double dVal);
    int insertCentered(int row, int col, int fieldLength,
        const QString text);
    int insertCentered(int row, int col, int fieldLength, int iVal);
    int insertCentered(int row, int col, int fieldLength, int fractLength,
        double dVal);
    int insertRight(int row, int col, int fieldLength, const
                    QString text);
    int insertRight(int row, int col, int fieldLength, int iVal);
    int insertRight(int row, int col, int fieldLength, int fractLength,
        double dVal);
    std::pair<int, int> insertMatrix(int row, int col, const cbr::Matrix<double>& mat,
        int columnWidth, int columnSpacing);

    void writeObject(std::ostream& os) const;

private:
    QString intToStr(int iVal) const;
    QString intToStrLeadingZeroes(int iVal, size_t fieldLength) const;
    void insertElement(int row, int col, const QString text);
    std::pair<int,int> doubleElements(double dVal, int fractLength) const;
    LogicError insertFailureErr(int row, int col, const QString text) const;
    typedef std::set<ReportElement, std::less<ReportElement> > ReportElements;
    ReportElements elements_;

    QString formatExpDouble(double dVal, int fractLength = 15);
    QString formatDouble(double dVal, int fieldLength, int fractLength = 6);
    QString formatInt(int iVal, int fieldLength, int base = 10);
    int numPlaces(double dVal);
};
#endif


