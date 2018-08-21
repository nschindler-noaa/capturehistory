#ifndef ReportElement_H
#define ReportElement_H

// One element in a report, used by the class ReportBuilder

#include <string>
#include <iostream>


	class ReportElement
	{
	public:
		ReportElement(int row, int column, const std::string& text) :
		row_(row), column_(column), text_(text) {}
		~ReportElement() {}
		int row() const {return row_;}
		int column() const {return column_;}
		const std::string& text() const {return text_;}
		int length() const {return text_.length();}
		bool operator<(const ReportElement& rhs) const {
		return (row_ == rhs.row_ ? column_ < rhs.column_ : row_ < rhs.row_);}
		void writeObject(std::ostream& os) const {os << text_;}

	private:
		int row_;
		int column_;
		std::string text_;
	};

#endif
