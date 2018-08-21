/*
*/

#include <QTextEdit>
#include <QTextCursor>
#include <QTextFrame>
#include <QTextFrameFormat>

#include "OutputDockWidget.h"

using namespace cbr;

OutputDockWidget::OutputDockWidget(QWidget *parent) : QDockWidget("Output", parent),
	edit_(0)
{
	edit_ = new QTextEdit(this);
	edit_->setReadOnly(true);
	cursor_ = edit_->textCursor();

	QTextCursor cursor = edit_->textCursor();
	QTextFrame *currentFrame = cursor.currentFrame();
	QTextFrameFormat frameFormat = currentFrame->frameFormat();
	frameFormat.setMargin(10);
	currentFrame->setFrameFormat(frameFormat);
	edit_->ensureCursorVisible();

	setWidget(edit_);

	plain_.setFontPointSize(10);
	status_ = warning_ = error_ = plain_;

	error_.setForeground(QBrush(Qt::red));

	warning_.setFontItalic(true);

	heading_.setFontPointSize(12);
	heading_.setFontWeight(QFont::Bold);
}

void OutputDockWidget::append(const QString& s, OutputType outType) 
{

	switch (outType)
	{
	case Error :
		cursor_.insertText(s, error_);
		break;
	case Warning :
		cursor_.insertText(s, warning_);
		break;
	case Heading :
		cursor_.insertText(s, heading_);
		break;
	default :
		cursor_.insertText(s, status_);
		break;
	}

	cursor_.insertBlock();
	cursor_.movePosition(QTextCursor::End);
	edit_->setTextCursor(cursor_);
}