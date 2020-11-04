/****************************************************************************
** Meta object code from reading C++ file 'CbrPlotControls.h'
**
** Created: Mon Nov 2 11:18:29 2020
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/CbrPlotControls.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CbrPlotControls.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_cbr__CbrPlotControls[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      22,   21,   21,   21, 0x05,
      39,   21,   21,   21, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_cbr__CbrPlotControls[] = {
    "cbr::CbrPlotControls\0\0currentChanged()\0"
    "gridLevelChanged(int)\0"
};

void cbr::CbrPlotControls::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CbrPlotControls *_t = static_cast<CbrPlotControls *>(_o);
        switch (_id) {
        case 0: _t->currentChanged(); break;
        case 1: _t->gridLevelChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData cbr::CbrPlotControls::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject cbr::CbrPlotControls::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_cbr__CbrPlotControls,
      qt_meta_data_cbr__CbrPlotControls, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &cbr::CbrPlotControls::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *cbr::CbrPlotControls::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *cbr::CbrPlotControls::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_cbr__CbrPlotControls))
        return static_cast<void*>(const_cast< CbrPlotControls*>(this));
    return QWidget::qt_metacast(_clname);
}

int cbr::CbrPlotControls::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void cbr::CbrPlotControls::currentChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void cbr::CbrPlotControls::gridLevelChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
