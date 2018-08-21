#ifndef CbrStyle_h
#define CbrStyle_h

#include <QTextCharFormat>
#include <QTextTableFormat>
#include <QTextTableCellFormat>
#include <QTextBlockFormat>
#include <QTextFrameFormat>
#include <QTextListFormat>

namespace cbr 
{
	class CbrStyle 
	{
	public:
		CbrStyle();

	protected:
		QTextFrameFormat frameFormat;

		QTextBlockFormat defaultBlockFormat;
		QTextBlockFormat blockFormat;
		QTextBlockFormat hBlockFormat;
		QTextBlockFormat listBlockFormat;
		QTextBlockFormat brBlockFormat;
		QTextBlockFormat sectionBlockFormat;
		QTextBlockFormat rightBlockFormat;
		QTextBlockFormat leftBlockFormat;
		QTextBlockFormat centerBlockFormat;
		QTextBlockFormat headerBlockFormat;
		QTextBlockFormat leftHeaderBlockFormat;
		QTextBlockFormat layoutBlockFormat;

		QTextListFormat ul;
		QTextListFormat ol;
		QTextListFormat dl;

		QTextCharFormat p;
		QTextCharFormat b;
		QTextCharFormat em;
		QTextCharFormat plain; // for backwards compatibility
		QTextCharFormat strong; // for backwards compatibility
		QTextCharFormat h1;
		QTextCharFormat h2;
		QTextCharFormat h3;
		QTextCharFormat h4;
		QTextCharFormat error;

		QTextTableFormat tableFormat;
		QTextTableFormat layoutTableFormat;

		QTextTableCellFormat layoutTableCellFormat;
		QTextTableCellFormat th;
		QTextTableCellFormat th_border_bottom;
		QTextTableCellFormat td;
	};

}
#endif