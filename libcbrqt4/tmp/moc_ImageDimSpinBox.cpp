/****************************************************************************
** Meta object code from reading C++ file 'ImageDimSpinBox.h'
**
** Created: Mon Nov 2 11:18:06 2020
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/ImageDimSpinBox.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ImageDimSpinBox.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ImageDimSpinBox[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      21,   17,   16,   16, 0x0a,
      38,   33,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ImageDimSpinBox[] = {
    "ImageDimSpinBox\0\0rhs\0setDpi(int)\0type\0"
    "setDimType(DimType)\0"
};

void ImageDimSpinBox::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ImageDimSpinBox *_t = static_cast<ImageDimSpinBox *>(_o);
        switch (_id) {
        case 0: _t->setDpi((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->setDimType((*reinterpret_cast< DimType(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ImageDimSpinBox::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ImageDimSpinBox::staticMetaObject = {
    { &QSpinBox::staticMetaObject, qt_meta_stringdata_ImageDimSpinBox,
      qt_meta_data_ImageDimSpinBox, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ImageDimSpinBox::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ImageDimSpinBox::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ImageDimSpinBox::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ImageDimSpinBox))
        return static_cast<void*>(const_cast< ImageDimSpinBox*>(this));
    return QSpinBox::qt_metacast(_clname);
}

int ImageDimSpinBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSpinBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
