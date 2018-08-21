#ifndef OutputDockWidget_h
#define OutputDockWidget_h

#include <QDockWidget>
#include <QTextCharFormat>
#include <QTextCursor>

class QTextEdit;

namespace cbr
{
	class OutputDockWidget : public QDockWidget
	{

	public:
		enum OutputType { Status = 0, Warning, Error, Heading };
		OutputDockWidget(QWidget *parent = 0);

		void append(const QString& s, OutputType outType = Status);

	private:
		QTextEdit *edit_;
		QTextCursor cursor_;

		QTextCharFormat heading_;
		QTextCharFormat plain_;
		QTextCharFormat status_;
		QTextCharFormat error_;
		QTextCharFormat warning_;
	};
}

#endif