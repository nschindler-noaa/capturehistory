#ifndef SettingModel_H
#define SettingModel_H

#include <QtSql>
//#include <DbModel.h>
//#include <string>
#include <QStringList>

namespace cbr
{
    class SettingModel : public QSqlTableModel // public cbr::DbModel
	{
	public:
		enum FIELDS {
			ID = 0,
			KEY,
			POSITION,
			VALUE,
			NUM_FIELDS
		};

		SettingModel();
		~SettingModel() {}

		int getNumInputFields() const { return NUM_FIELDS; }

	private:
        static QStringList names;
        static QStringList types;
//		static const std::string names[];
//		static const std::string types[];
	};
}

#endif
