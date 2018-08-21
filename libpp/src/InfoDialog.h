/*
 *
 */


#include <qdialog.h>

#include "ui_InfoDialog.h"   

class InfoDialog : public QDialog, public Ui::InfoDialog
{
public:
        InfoDialog(QWidget* parent, Qt::WindowFlags fl = 0)
		: QDialog(parent, fl)
	{ setupUi(this); }
};
