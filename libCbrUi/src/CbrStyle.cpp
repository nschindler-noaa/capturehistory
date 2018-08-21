/*
 * Class which want to use these should inherit from this class, probably as an
 * additional mulitply inherited class.
*/

#include "CbrStyle.h"

using namespace cbr;

CbrStyle::CbrStyle()
{
	const int top_margin = 12;
	const int bottom_margin = 10;
	const int frame_margin = 10;
	const int left_margin = 10;

	//QColor headerColor(240, 248, 255);
	QColor headerColor(245, 250, 255);
	//QColor headerColor(250, 252, 255);

	frameFormat.setTopMargin(0);
	frameFormat.setRightMargin(frame_margin);
	frameFormat.setBottomMargin(frame_margin);
	frameFormat.setLeftMargin(frame_margin);

	//defaultBlockFormat.setBackground(QColor("lightGray"));

	blockFormat = defaultBlockFormat;
	blockFormat.setTopMargin(top_margin);
	blockFormat.setBottomMargin(bottom_margin);

	listBlockFormat = defaultBlockFormat;
	//listBlockFormat.setBackground(Qt::blue);

	hBlockFormat = defaultBlockFormat;
	hBlockFormat.setTopMargin(0);
	hBlockFormat.setBottomMargin(15);
	//hBlockFormat.setBackground(Qt::red);

	brBlockFormat = defaultBlockFormat;
	brBlockFormat.setTopMargin(0);

	sectionBlockFormat = blockFormat;
	sectionBlockFormat.setTopMargin(1.5 * top_margin);

	rightBlockFormat = defaultBlockFormat;
	rightBlockFormat.setLeftMargin(4);
	rightBlockFormat.setRightMargin(4);
	rightBlockFormat.setAlignment(Qt::AlignRight);

	leftBlockFormat = rightBlockFormat;
	leftBlockFormat.setAlignment(Qt::AlignLeft);

	centerBlockFormat = rightBlockFormat;
	centerBlockFormat.setAlignment(Qt::AlignHCenter);

	headerBlockFormat = centerBlockFormat;
	headerBlockFormat.setLeftMargin(0);
	headerBlockFormat.setRightMargin(0);
	headerBlockFormat.setTopMargin(0);
	headerBlockFormat.setBottomMargin(0);
	headerBlockFormat.setBackground(headerColor);

	leftHeaderBlockFormat = leftBlockFormat;
	leftHeaderBlockFormat.setBackground(headerColor);

	layoutBlockFormat = brBlockFormat;
	layoutBlockFormat.setLeftMargin(left_margin);

	ul.setStyle(QTextListFormat::ListDisc);
	ol.setStyle(QTextListFormat::ListDecimal);
	//dl.setStyle();

	p.setFontPointSize(8);
	p.setFontUnderline(false);
	p.setFontWeight(QFont::Normal);
	p.setForeground(QColor("#000000"));
	p.setFontItalic(false);

	em = p;
	em.setFontItalic(true);

	b = p;
	b.setFontWeight(QFont::Bold);
	b.setForeground(QColor("#000000"));

	h4 = b;
	
	h3 = h4;
	h3.setFontPointSize(9);

	h2 = h3;
	h2.setFontPointSize(10);

	h1 = h2;
	h1.setFontPointSize(12);
	h1.setFontUnderline(true);

	td = p.toTableCellFormat();
	td.setLeftPadding(10);
	td.setRightPadding(10);

	th = td;
	th.setFontWeight(QFont::Bold);  

	th_border_bottom = th;
	th_border_bottom.setUnderlineStyle(QTextCharFormat::SingleUnderline);

	error = p;
	error.setForeground(QColor("#ff0000"));

	// table formats
	tableFormat.setAlignment(Qt::AlignLeft);
	tableFormat.setBackground(QColor("#ffffff"));
	tableFormat.setCellPadding(2);
	tableFormat.setCellSpacing(0);
	tableFormat.setBorder(1);
	tableFormat.setBorderStyle(QTextFrameFormat::BorderStyle_Solid);
	tableFormat.setBorderBrush(QBrush(Qt::lightGray));
	tableFormat.setTopMargin(top_margin);
	tableFormat.setBottomMargin(bottom_margin);
	tableFormat.setLeftMargin(0);

	layoutTableFormat.setBorder(0);
	layoutTableFormat.setTopMargin(top_margin);
	layoutTableFormat.setBottomMargin(bottom_margin);
	layoutTableFormat.setLeftMargin(left_margin);

	layoutTableCellFormat.setLeftPadding(10);
}