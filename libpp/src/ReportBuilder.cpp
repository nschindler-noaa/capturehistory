#include <iostream>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <limits>
#include <cfloat>
#include <string>
#include "ReportBuilder.h"
#include "LogicError.h"
using namespace std;
using namespace cbr;

int ReportBuilder::insertLeft(int row, int col, const QString text)
{
    insertElement(row, col, text);
    return (col+text.count());
}

int ReportBuilder::insertLeft(int row, int col, int fieldLength, const QString text)
{
    QString outtext(text);
    if (outtext.count() > fieldLength)
        outtext.truncate(fieldLength);
    while (outtext.count() < fieldLength)
        outtext.append(' ');
    insertLeft(row, col, outtext);
//	if (text.length() > fieldLength) {
//		string str = string(text.data(),fieldLength);
//		insertLeft(row,col,str);
//	}
//	else
//		insertLeft(row,col,text);
    return (col + fieldLength);
}

int ReportBuilder::insertLeft(int row, int col, int fieldLength, int fractLength,
    double dVal)
{
    QString outtext(formatDouble(dVal, fieldLength, fractLength));
    return insertLeft(row, col, fieldLength, outtext);
//	ostringstream oss;
//	oss << fixed << setprecision(fractLength) << dVal;
//	if (oss.str().size() > fieldLength)
//		insertLeft(row,col,string(fieldLength,'*'));
//	else
//		insertLeft(row,col,oss.str());
//	return col + fieldLength;
}

int ReportBuilder::insertLeft(int row, int col, int fractLength, double dVal)
{
    int dec = numPlaces(dVal);
    QString outtext(formatDouble(dVal, fractLength, (fractLength-(dec+1))));
    if (dVal <= -DBL_MAX)
        outtext.fill('*', fractLength);
    return insertLeft(row, col, outtext);
//		return insertLeft(row, col, outtext.fill('*', fractLength));
//	else {
//		ostringstream oss;
//		oss << setprecision(fractLength) << fixed << dVal;
//		return insertLeft(row,col,oss.str());
//	}
}

// TODO: Fix
int ReportBuilder::insertLeft(int row, int col, int fieldLength, int iVal)
{
    QString outtext(formatInt(iVal, fieldLength));
    return insertLeft(row, col, fieldLength, outtext);
//	ostringstream oss;
//	oss << iVal;
//	if (oss.str().size() > fieldLength)
//		insertLeft(row, col, string(fieldLength,'*'));
//	else
//		insertLeft(row,col, oss.str());
//	return col + fieldLength;
}

int ReportBuilder::insertLeft(int row, int col, int iVal)
{
    QString outtext(QString::number(iVal));
    return insertLeft(row, col, outtext);
//	ostringstream oss;
//	oss << iVal;
//	return insertLeft(row,col,oss.str());
}

int ReportBuilder::insertLeftExp(int row, int col, double dVal)
{
    QString outtext(formatExpDouble(dVal));
    return insertLeft(row, col, outtext);
//	ostringstream oss;
//	oss << scientific << setprecision(15) << dVal;
//	return insertLeft(row,col,oss.str());
}

int ReportBuilder::insertCentered(int row, int col, int fieldLength, const QString text)
{
    QString useText(text);
    if (text.count() > fieldLength)
        useText.truncate(fieldLength);//string(text.data(),fieldLength);
    int startCol = col + (fieldLength%2 == 0 ?
        fieldLength/2 - (useText.length()+1)/2 :
    fieldLength/2 - useText.length()/2);
    insertLeft(row,startCol,useText);
    return (col + fieldLength);
}

int ReportBuilder::insertCentered(int row, int col, int fieldLength, int iVal)
{
    QString outtext(QString::number(iVal));
    if (outtext.count() > fieldLength)
        outtext.fill('*', fieldLength);
//	ostringstream oss;
//	oss << iVal;
//	if (oss.str().size() > fieldLength)
//		insertLeft(row,col,string(fieldLength,'*'));
//	else
//		insertCentered(row,col,fieldLength,oss.str());
    return insertCentered(row, col, fieldLength, outtext); //col + fieldLength;
}

int ReportBuilder::insertCentered(int row, int col, int fieldLength,
    int fractLength, double dVal)
{
    QString outtext(QString::number(dVal, 'f', fractLength));
    if (outtext.count() > fieldLength)
        outtext.fill('*', fieldLength);
    return insertCentered(row, col, fieldLength, outtext);
//	ostringstream oss;
//	oss << fixed << setprecision(fractLength) << dVal;
//	if (oss.str().size() >  fieldLength)
//		insertLeft(row,col,string(fieldLength,'*'));
//	else
//		insertCentered(row,col,fieldLength,oss.str());
//	return col + fieldLength;
}

int ReportBuilder::insertRight(int row, int col, int fieldLength,
    const QString text)
{
    QString outtext = text;
    outtext.truncate(fieldLength-1);
    while (outtext.count() < fieldLength-1)
        outtext.prepend(' ');
//    std::string str = text.toStdString().substr(0, fieldLength-1);
//	if (text.size() > fieldLength)
//		insertElement(row,col,text.substr(0,fieldLength-1));
//	else {
//		ostringstream oss;
//		oss << right << setw(fieldLength) << text;
//		insertLeft(row,col,oss.str());
//	}
    return insertLeft(row, col, outtext);//col + fieldLength;
}

int ReportBuilder::insertRight(int row, int col, int fieldLength, int iVal)
{
    QString outtext(formatInt(iVal, fieldLength));
    return insertRight(row, col, fieldLength, outtext);
//	ostringstream oss;
//	oss << right << setw(fieldLength) << iVal;
//	if (oss.str().size() > fieldLength)
//		return insertLeft(row,col,string(fieldLength,'*'));
//	else
//		return insertLeft(row,col,oss.str());
}

int ReportBuilder::insertRight(int row, int col, int fieldLength, int fractLength,
    double dVal)
{
    QString outtext(formatDouble(dVal, fieldLength, fractLength));

    return insertRight(row, col, fieldLength, outtext);
//	ostringstream oss;
//	oss << right << fixed << setprecision(fractLength) << setw(fieldLength) << dVal;
//	if (oss.str().size() > fieldLength)
//		return insertLeft(row,col,string(fieldLength,'*'));
//	else
//		return insertLeft(row,col,oss.str());
}

pair<int, int> ReportBuilder::insertMatrix(int row, int col, const Matrix<double>& mat,
    int columnWidth, int columnSpacing)
{
    for (int i=0; i < mat.rows(); ++i) {
        for (int j=0; j < mat.cols(); ++j) {
            insertLeftExp(row,col,mat(i,j));
            col += columnWidth + columnSpacing;
        }
        col = 0;
        ++row;
    }
    return pair<int, int>(row,col);
}
void ReportBuilder::writeObject(ostream& os) const
{
    int currentColumn = 0;
    int currentRow = 0;

    for (ReportElements::const_iterator iter=elements_.begin();
        iter != elements_.end(); ++iter)
    {
        if ((*iter).row() > currentRow) {
            for (int i=currentRow; i < (*iter).row(); i++)
                os << "\n";
            currentRow = (*iter).row();
            currentColumn = 0;
        }
        for (int column=currentColumn; column < (*iter).column(); column++)
            os << " ";
        (*iter).writeObject(os);
        currentColumn = (*iter).column() + (*iter).length();
    }
}


void ReportBuilder::insertElement(int row, int col, const QString text)
{
    pair<ReportElements::iterator, bool> status =
        elements_.insert(ReportElement(row,col,text));
    if (!status.second)
        throw insertFailureErr(row,col,text);
}


LogicError ReportBuilder::insertFailureErr(int row, int col, const QString text) const
{
    QString qstr (QString("Report -- insertion failure for row %1, col %2, string = %3").arg(
        QString::number(row), QString:: number(col), text));
    return LogicError (qstr);
}

QString ReportBuilder::formatExpDouble(double dVal, int fractLength)
{
    QString outtext(QString::number(dVal, 'e', fractLength));
    outtext.truncate(fractLength);
    return outtext;
}

QString ReportBuilder::formatDouble(double dVal, int fieldLength, int fractLength)
{
    QString outtext(QString::number(dVal, 'f', fractLength));
    if (outtext.count() > fieldLength)
        outtext.fill('*', fieldLength);
    return outtext;
}

QString ReportBuilder::formatInt(int iVal, int fieldLength, int base)
{
    QString outtext(QString::number(iVal, base));
    if (outtext.count() > fieldLength)
        outtext.fill('*', fieldLength);
    return outtext;
}

int ReportBuilder::numPlaces(double dVal)
{
    int count = 0;
    double checkVal = dVal;
    while (checkVal > 1.0) {
        checkVal /= 10.0;
        count++;
    }
    return count;
}

