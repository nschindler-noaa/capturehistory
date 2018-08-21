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

int ReportBuilder::insertLeft(int row, int col, const string& text)
{
	insertElement(row,col,text);
	return col+text.length();
}

int ReportBuilder::insertLeft(int row, int col, size_t fieldLength, const string& text)
{
	if (text.length() > fieldLength) {
		string str = string(text.data(),fieldLength);
		insertLeft(row,col,str);
	}
	else
		insertLeft(row,col,text);
	return col + fieldLength;
}

int ReportBuilder::insertLeft(int row, int col, size_t fieldLength, int fractLength,
	double dVal)
{
	ostringstream oss;
	oss << fixed << setprecision(fractLength) << dVal;
	if (oss.str().size() > fieldLength)
		insertLeft(row,col,string(fieldLength,'*'));
	else
		insertLeft(row,col,oss.str());
	return col + fieldLength;
}

int ReportBuilder::insertLeft(int row, int col, int fractLength, double dVal)
{
	if (dVal <= -DBL_MAX)
		return insertLeft(row,col,string(fractLength,'*'));
	else {
		ostringstream oss;
		oss << setprecision(fractLength) << fixed << dVal;
		return insertLeft(row,col,oss.str());
	}
}

// TODO: Fix
//int ReportBuilder::insertLeft(int row, int col, size_t fieldLength, int iVal)
//{
//	ostringstream oss;
//	oss << iVal;
//	if (oss.str().size() > fieldLength)
//		insertLeft(row, col, string(fieldLength,'*'));
//	else
//		insertLeft(row,col, oss.str());
//	return col + fieldLength;
//}

int ReportBuilder::insertLeft(int row, int col, int iVal)
{
	ostringstream oss;
	oss << iVal;
	return insertLeft(row,col,oss.str());
}

int ReportBuilder::insertLeftExp(int row, int col, double dVal)
{
	ostringstream oss;
	oss << scientific << setprecision(15) << dVal;
	return insertLeft(row,col,oss.str());
}

int ReportBuilder::insertCentered(int row, int col, size_t fieldLength, const string& text)
{
	string useText(text);
	if (text.length() > fieldLength)
		useText = string(text.data(),fieldLength);
	int startCol = col + (fieldLength%2 == 0 ?
		fieldLength/2 - (useText.length()+1)/2 :
	fieldLength/2 - useText.length()/2);
	insertLeft(row,startCol,useText);
	return col + fieldLength;
}

int ReportBuilder::insertCentered(int row, int col, size_t fieldLength, int iVal)
{
	ostringstream oss;
	oss << iVal;
	if (oss.str().size() > fieldLength)
		insertLeft(row,col,string(fieldLength,'*'));
	else
		insertCentered(row,col,fieldLength,oss.str());
	return col + fieldLength;
}

int ReportBuilder::insertCentered(int row, int col, size_t fieldLength,
	int fractLength, double dVal)
{
	ostringstream oss;
	oss << fixed << setprecision(fractLength) << dVal;
	if (oss.str().size() >  fieldLength)
		insertLeft(row,col,string(fieldLength,'*'));
	else
		insertCentered(row,col,fieldLength,oss.str());
	return col + fieldLength;
}

int ReportBuilder::insertRight(int row, int col, size_t fieldLength,
	const string& text)
{

	if (text.size() > fieldLength)
		insertElement(row,col,text.substr(0,fieldLength-1));
	else {
		ostringstream oss;
		oss << right << setw(fieldLength) << text;
		insertLeft(row,col,oss.str());
	}
	return col + fieldLength;
}

int ReportBuilder::insertRight(int row, int col, size_t fieldLength, int iVal)
{
	ostringstream oss;
	oss << right << setw(fieldLength) << iVal;
	if (oss.str().size() > fieldLength)
		return insertLeft(row,col,string(fieldLength,'*'));
	else
		return insertLeft(row,col,oss.str());
}

int ReportBuilder::insertRight(int row, int col, size_t fieldLength, int fractLength,
	double dVal)
{
	ostringstream oss;
	oss << right << fixed << setprecision(fractLength) << setw(fieldLength) << dVal;
	if (oss.str().size() > fieldLength)
		return insertLeft(row,col,string(fieldLength,'*'));
	else
		return insertLeft(row,col,oss.str());
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

// TODO: Fix
void ReportBuilder::insertElement(int row, int col, const string& text)
{
	pair<ReportElements::iterator, bool> status =
		elements_.insert(ReportElement(row,col,text));
	//		if (!status.second)
	//			throw insertFailureErr(row,col,text);
}

// TODO: Fix
//LogicError ReportBuilder::insertFailureErr(int row, int col, const string& text) const
//{
//	ostringstream oss;
//	oss << "Report -- insertion failure for row " << row << ", col " << col <<
//		", string = " << text;
//	return LogicError(string(oss.str()));
//}
