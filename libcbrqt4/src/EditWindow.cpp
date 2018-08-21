/*
*
*/

#include <qfile.h>
#include <QTextEdit>
//#include <Q3TextEdit>
#include <qprinter.h>
#include <qpainter.h>
#include <QPaintDevice>
//#include <q3paintdevicemetrics.h>
#include <qstring.h>
#include <qfile.h>
#include <QPlainTextEdit>
//#include <q3simplerichtext.h>
#include <QFileDialog>
//#include <q3filedialog.h>
#include <QMessageBox>
#include <qevent.h>
//Added by qt3to4:
#include <QTextStream>
#include <QCloseEvent>

#include "EditWindow.h"

/* 
*  Constructs a EditWindow which is a child of 'parent', with the 
*  name 'name' and widget flags set to 'f' 
*/
EditWindow::EditWindow(QWidget* parent,  const char* name, Qt::WindowFlags fl)
    : QMainWindow (parent, fl)//, changed(false)
//    : Q3MainWindow (parent, name, fl)//, changed(false)
{
    setObjectName(QString(name));
    setWindowTitle(QString(name));
	setupUi (this);
	connect (fileExitAction, SIGNAL (triggered()), this, SLOT (close()));
	connect (filePrintAction, SIGNAL (triggered()), this, SLOT (print()));
	connect (fileSaveAction, SIGNAL (triggered()), this, SLOT (save()));
	connect (fileSave_asAction, SIGNAL (triggered()), this, SLOT (saveAs()));
	connect (fileOpenAction, SIGNAL (triggered()), this, SLOT (open()));
	connect (textEdit, SIGNAL (textChanged()), this, SLOT (doTextChanged()));


}

/*  
*  Destroys the object and frees any allocated resources
*/
EditWindow::~EditWindow()
{
	// no need to delete child widgets, Qt does it all for us
}


void EditWindow::setSource(const QString& file)
{

	if (QFile::exists(file))
	{
		QFile in(file);
		if (in.open(QIODevice::ReadOnly)) {
			currentFile = file;
            setWindowTitle(currentFile);
//			setCaption(currentFile);

			QTextStream ts(&in);
			textEdit->clear();
			textEdit->setText(ts.read());
			twChanged = false;
		}
	}
}

void EditWindow::print()
{
	QPrinter printer;
	printer.setFullPage(true);
	if (printer.setup(this)) {
		QPainter p(&printer);

		// get the device sizes
		Q3PaintDeviceMetrics metrics(p.device());
		int dpix = metrics.logicalDpiX();
		int dpiy = metrics.logicalDpiY();
		const int margin = 72; // pt
		QRect body(margin * dpix / 72, margin * dpiy / 72,
			metrics.width() - margin * dpix / 72 * 2,
			metrics.height() - margin * dpiy / 72 * 2);

		// get the font
		QFont font(textEdit->font());

		// set up the rich text object
		QString outstring = "<pre>" + textEdit->text() + "</pre>";
		Q3SimpleRichText richText(outstring, font);
		richText.setWidth(&p, body.width());


		// initialize view to the display 
		QRect view(body);
		int page = 1;
		int totalPrinted = 0;
		do {
			// print the page
			richText.draw(&p, body.left(), body.top(), view, colorGroup());

			// move the view and adjust the printer coordinates 
			view.moveBy(0, body.height());
			totalPrinted += body.height();
			p.translate(0 , -body.height());

			// print the page number
			p.setFont(font);
			QString pageNum = QString::number(page);
			p.drawText(view.right() - p.fontMetrics().width(pageNum),
				view.bottom() + p.fontMetrics().ascent() + 5, 
				pageNum);

			// check if there are more pages
			if (totalPrinted  >= richText.height())
				break;
			printer.newPage();
			page++;
		} while (true);
	}
}

void EditWindow::open()
{
	setSource(Q3FileDialog::getOpenFileName("","All file (*.*)", this));
}

void EditWindow::save()
{
	if (currentFile.isNull())
		saveAs();
	else
		saveFile(currentFile);
}


void EditWindow::saveAs()
{
	saveFile(Q3FileDialog::getSaveFileName("","All file (*.*)", this));
}

void EditWindow::saveFile(const QString& file)
{
	if (!file.isNull())
	{
		QFile f(file);
		if (f.open(IO_WriteOnly | IO_Translate)) {    // file opened successfully
			QTextStream t(&f);        // use a text stream	
			t << textEdit->text() << endl;
		}
		currentFile = file;
		setCaption(currentFile);

		f.close();
	}
}


void EditWindow::doTextChanged()
{
	twChanged = true;
}

void EditWindow::closeEvent(QCloseEvent* e)
{
	if (twChanged)
	{
		int ans = QMessageBox::question(this, "ROSTER", "Save changes?",
			QMessageBox::Yes, QMessageBox::No, QMessageBox::Cancel);

		if (ans == QMessageBox::Yes)
		{
			save();
			e->accept();
		}
		else if (ans == QMessageBox::Cancel)
			e->ignore();
		else if (ans == QMessageBox::No)
			e->accept();
	}
	else
		e->accept();

}

