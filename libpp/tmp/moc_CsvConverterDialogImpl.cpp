/****************************************************************************
** Meta object code from reading C++ file 'CsvConverterDialogImpl.h'
**
** Created: Thu Mar 10 16:46:42 2022
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/CsvConverterDialogImpl.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CsvConverterDialogImpl.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CsvConverterDialogImpl[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      33,   24,   23,   23, 0x0a,
      58,   23,   23,   23, 0x0a,
      67,   23,   23,   23, 0x0a,
      76,   23,   23,   23, 0x0a,
      94,   90,   23,   23, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CsvConverterDialogImpl[] = {
    "CsvConverterDialogImpl\0\0fileName\0"
    "csvFileSelected(QString)\0accept()\0"
    "reject()\0updateTable()\0rhs\0"
    "doTypeToggled(bool)\0"
};

void CsvConverterDialogImpl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CsvConverterDialogImpl *_t = static_cast<CsvConverterDialogImpl *>(_o);
        switch (_id) {
        case 0: _t->csvFileSelected((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->accept(); break;
        case 2: _t->reject(); break;
        case 3: _t->updateTable(); break;
        case 4: _t->doTypeToggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CsvConverterDialogImpl::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CsvConverterDialogImpl::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CsvConverterDialogImpl,
      qt_meta_data_CsvConverterDialogImpl, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CsvConverterDialogImpl::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CsvConverterDialogImpl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CsvConverterDialogImpl::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CsvConverterDialogImpl))
        return static_cast<void*>(const_cast< CsvConverterDialogImpl*>(this));
    if (!strcmp(_clname, "Ui::CsvConverterDialog"))
        return static_cast< Ui::CsvConverterDialog*>(const_cast< CsvConverterDialogImpl*>(this));
    return QDialog::qt_metacast(_clname);
}

int CsvConverterDialogImpl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
