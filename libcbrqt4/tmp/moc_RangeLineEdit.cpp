/****************************************************************************
** Meta object code from reading C++ file 'RangeLineEdit.h'
**
** Created: Mon Nov 2 11:18:08 2020
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/RangeLineEdit.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'RangeLineEdit.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_RangeLineEdit[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      45,   40,   14,   14, 0x0a,
      66,   62,   14,   14, 0x0a,
      88,   83,   14,   14, 0x0a,
     114,  110,   14,   14, 0x0a,
     137,  133,   14,   14, 0x0a,
     156,   14,   14,   14, 0x0a,
     178,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_RangeLineEdit[] = {
    "RangeLineEdit\0\0rangeAlreadySet(QString)\0"
    "text\0setText(QString)\0rhs\0setRangeOk(bool)\0"
    "type\0setEditType(EditType)\0min\0"
    "setEditMin(double)\0max\0setEditMax(double)\0"
    "setRangeEnabled(bool)\0setRangeAllowed(bool)\0"
};

void RangeLineEdit::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        RangeLineEdit *_t = static_cast<RangeLineEdit *>(_o);
        switch (_id) {
        case 0: _t->rangeAlreadySet((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->setText((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->setRangeOk((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->setEditType((*reinterpret_cast< EditType(*)>(_a[1]))); break;
        case 4: _t->setEditMin((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 5: _t->setEditMax((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 6: _t->setRangeEnabled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->setRangeAllowed((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData RangeLineEdit::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject RangeLineEdit::staticMetaObject = {
    { &QLineEdit::staticMetaObject, qt_meta_stringdata_RangeLineEdit,
      qt_meta_data_RangeLineEdit, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &RangeLineEdit::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *RangeLineEdit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *RangeLineEdit::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RangeLineEdit))
        return static_cast<void*>(const_cast< RangeLineEdit*>(this));
    return QLineEdit::qt_metacast(_clname);
}

int RangeLineEdit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLineEdit::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void RangeLineEdit::rangeAlreadySet(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
