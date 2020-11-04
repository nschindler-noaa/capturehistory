/****************************************************************************
** Meta object code from reading C++ file 'newEditWindow.h'
**
** Created: Mon Nov 2 11:18:09 2020
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/newEditWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'newEditWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_newEditWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   15,   14,   14, 0x0a,
      39,   14,   14,   14, 0x0a,
      47,   14,   14,   14, 0x0a,
      54,   14,   14,   14, 0x0a,
      61,   14,   14,   14, 0x0a,
      70,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_newEditWindow[] = {
    "newEditWindow\0\0file\0setSource(QString)\0"
    "print()\0open()\0save()\0saveAs()\0"
    "doTextChanged()\0"
};

void newEditWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        newEditWindow *_t = static_cast<newEditWindow *>(_o);
        switch (_id) {
        case 0: _t->setSource((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->print(); break;
        case 2: _t->open(); break;
        case 3: _t->save(); break;
        case 4: _t->saveAs(); break;
        case 5: _t->doTextChanged(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData newEditWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject newEditWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_newEditWindow,
      qt_meta_data_newEditWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &newEditWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *newEditWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *newEditWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_newEditWindow))
        return static_cast<void*>(const_cast< newEditWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int newEditWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
