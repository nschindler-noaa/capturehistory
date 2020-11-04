/****************************************************************************
** Meta object code from reading C++ file 'TextWindowSimple.h'
**
** Created: Mon Nov 2 11:18:34 2020
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/TextWindowSimple.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TextWindowSimple.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TextWindowSimple[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      22,   18,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
      39,   17,   17,   17, 0x0a,
      55,   17,   17,   17, 0x0a,
      70,   17,   17,   17, 0x0a,
      89,   17,   17,   17, 0x0a,
     109,  107,   17,   17, 0x0a,
     141,  139,   17,   17, 0x0a,
     161,  139,   17,   17, 0x0a,
     178,   17,   17,   17, 0x0a,
     191,  186,   17,   17, 0x0a,
     211,  206,   17,   17, 0x0a,
     235,  230,   17,   17, 0x0a,
     262,   17,   17,   17, 0x0a,
     281,   17,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_TextWindowSimple[] = {
    "TextWindowSimple\0\0rhs\0windowOpen(bool)\0"
    "doPrintAction()\0doSaveAction()\0"
    "doClearAllAction()\0doWindowClosing()\0"
    "f\0setTextFormat(Qt::TextFormat)\0s\0"
    "appendText(QString)\0setText(QString)\0"
    "clear()\0font\0setFont(QFont)\0file\0"
    "setSource(QString)\0text\0"
    "doFindTextChanged(QString)\0"
    "doFindNextButton()\0doFindPreviousButton()\0"
};

void TextWindowSimple::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        TextWindowSimple *_t = static_cast<TextWindowSimple *>(_o);
        switch (_id) {
        case 0: _t->windowOpen((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->doPrintAction(); break;
        case 2: _t->doSaveAction(); break;
        case 3: _t->doClearAllAction(); break;
        case 4: _t->doWindowClosing(); break;
        case 5: _t->setTextFormat((*reinterpret_cast< Qt::TextFormat(*)>(_a[1]))); break;
        case 6: _t->appendText((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->setText((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: _t->clear(); break;
        case 9: _t->setFont((*reinterpret_cast< const QFont(*)>(_a[1]))); break;
        case 10: _t->setSource((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 11: _t->doFindTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 12: _t->doFindNextButton(); break;
        case 13: _t->doFindPreviousButton(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData TextWindowSimple::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject TextWindowSimple::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_TextWindowSimple,
      qt_meta_data_TextWindowSimple, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TextWindowSimple::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TextWindowSimple::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TextWindowSimple::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TextWindowSimple))
        return static_cast<void*>(const_cast< TextWindowSimple*>(this));
    if (!strcmp(_clname, "Ui_TextWindowSimple"))
        return static_cast< Ui_TextWindowSimple*>(const_cast< TextWindowSimple*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int TextWindowSimple::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void TextWindowSimple::windowOpen(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
