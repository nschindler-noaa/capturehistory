/****************************************************************************
** Meta object code from reading C++ file 'NavPanelModel.h'
**
** Created: Mon Nov 2 11:18:33 2020
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/NavPanelModel.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'NavPanelModel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_cbr__NavPanelModel[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      25,   20,   19,   19, 0x05,

 // slots: signature, parameters, type, tag, flags
      68,   59,   19,   19, 0x0a,
     104,   59,   19,   19, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_cbr__NavPanelModel[] = {
    "cbr::NavPanelModel\0\0item\0"
    "currentItemChanged(NavPanelItem*)\0"
    "item,rhs\0setItemSelected(NavPanelItem*,bool)\0"
    "setItemActive(NavPanelItem*,bool)\0"
};

void cbr::NavPanelModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        NavPanelModel *_t = static_cast<NavPanelModel *>(_o);
        switch (_id) {
        case 0: _t->currentItemChanged((*reinterpret_cast< NavPanelItem*(*)>(_a[1]))); break;
        case 1: _t->setItemSelected((*reinterpret_cast< NavPanelItem*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 2: _t->setItemActive((*reinterpret_cast< NavPanelItem*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData cbr::NavPanelModel::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject cbr::NavPanelModel::staticMetaObject = {
    { &QAbstractItemModel::staticMetaObject, qt_meta_stringdata_cbr__NavPanelModel,
      qt_meta_data_cbr__NavPanelModel, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &cbr::NavPanelModel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *cbr::NavPanelModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *cbr::NavPanelModel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_cbr__NavPanelModel))
        return static_cast<void*>(const_cast< NavPanelModel*>(this));
    return QAbstractItemModel::qt_metacast(_clname);
}

int cbr::NavPanelModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractItemModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void cbr::NavPanelModel::currentItemChanged(NavPanelItem * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
