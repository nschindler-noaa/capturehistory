/****************************************************************************
** Meta object code from reading C++ file 'DataConverterImpl.h'
**
** Created: Mon Nov 2 11:22:35 2020
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/DataConverterImpl.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DataConverterImpl.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DataConverterImpl[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x05,

 // slots: signature, parameters, type, tag, flags
      35,   18,   18,   18, 0x0a,
      45,   18,   18,   18, 0x0a,
      55,   18,   18,   18, 0x0a,
      72,   18,   18,   18, 0x0a,
      89,   18,   18,   18, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_DataConverterImpl[] = {
    "DataConverterImpl\0\0dataConverted()\0"
    "refresh()\0convert()\0obsFileChanged()\0"
    "tagFileChanged()\0dataDirChanged(QString)\0"
};

void DataConverterImpl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DataConverterImpl *_t = static_cast<DataConverterImpl *>(_o);
        switch (_id) {
        case 0: _t->dataConverted(); break;
        case 1: _t->refresh(); break;
        case 2: _t->convert(); break;
        case 3: _t->obsFileChanged(); break;
        case 4: _t->tagFileChanged(); break;
        case 5: _t->dataDirChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DataConverterImpl::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DataConverterImpl::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DataConverterImpl,
      qt_meta_data_DataConverterImpl, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DataConverterImpl::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DataConverterImpl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DataConverterImpl::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DataConverterImpl))
        return static_cast<void*>(const_cast< DataConverterImpl*>(this));
    if (!strcmp(_clname, "Ui::DataConverter"))
        return static_cast< Ui::DataConverter*>(const_cast< DataConverterImpl*>(this));
    return QDialog::qt_metacast(_clname);
}

int DataConverterImpl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void DataConverterImpl::dataConverted()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
