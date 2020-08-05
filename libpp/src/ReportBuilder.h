#ifndef ReportBuilder_H
#define ReportBuilder_H

// Provides the ability to build and write a text report by placing
// text on a page independent of other text, and in any order,
// regardless of where it lies on the page.

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

	int insertLeft(int row, int col, const std::string& text);
	int insertLeft(int row, int col, size_t fieldLength, const std::string& text);
	int insertLeft(int row, int col, size_t fieldLength, int fractLength,
		double dVal);
	int insertLeft(int row, int col, int fractLength, double dVal);
	//		int insertLeft(int row, int col, size_t fieldLength, int iVal);
	int insertLeft(int row, int col, int iVal);
	int insertLeftExp(int row, int col, double dVal);
	int insertCentered(int row, int col, size_t fieldLength,
		const std::string& text);
	int insertCentered(int row, int col, size_t fieldLength, int iVal);
	int insertCentered(int row, int col, size_t fieldLength, int fractLength,
		double dVal);
	int insertRight(int row, int col, size_t fieldLength, const std::string& text);
	int insertRight(int row, int col, size_t fieldLength, int iVal);
	int insertRight(int row, int col, size_t fieldLength, int fractLength,
		double dVal);
	std::pair<int, int> insertMatrix(int row, int col, const cbr::Matrix<double>& mat,
		int columnWidth, int columnSpacing);

	void writeObject(std::ostream& os) const;

private:
	std::string intToStr(int iVal) const;
	std::string intToStrLeadingZeroes(int iVal, size_t fieldLength) const;
	void insertElement(int row, int col, const std::string& text);
	std::pair<int,int> doubleElements(double dVal, int fractLength) const;
    LogicError insertFailureErr(int row, int col, const std::string& text) const;
	typedef std::set<ReportElement, std::less<ReportElement> > ReportElements;
	ReportElements elements_;
};
#endif


