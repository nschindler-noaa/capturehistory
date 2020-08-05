/****************************************************************************
** Meta object code from reading C++ file 'TextWindowSimple.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/TextWindowSimple.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TextWindowSimple.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TextWindowSimple_t {
    QByteArrayData data[23];
    char stringdata0[240];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TextWindowSimple_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TextWindowSimple_t qt_meta_stringdata_TextWindowSimple = {
    {
QT_MOC_LITERAL(0, 0, 16), // "TextWindowSimple"
QT_MOC_LITERAL(1, 17, 10), // "windowOpen"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 3), // "rhs"
QT_MOC_LITERAL(4, 33, 13), // "doPrintAction"
QT_MOC_LITERAL(5, 47, 12), // "doSaveAction"
QT_MOC_LITERAL(6, 60, 16), // "doClearAllAction"
QT_MOC_LITERAL(7, 77, 15), // "doWindowClosing"
QT_MOC_LITERAL(8, 93, 13), // "setTextFormat"
QT_MOC_LITERAL(9, 107, 14), // "Qt::TextFormat"
QT_MOC_LITERAL(10, 122, 1), // "f"
QT_MOC_LITERAL(11, 124, 10), // "appendText"
QT_MOC_LITERAL(12, 135, 1), // "s"
QT_MOC_LITERAL(13, 137, 7), // "setText"
QT_MOC_LITERAL(14, 145, 5), // "clear"
QT_MOC_LITERAL(15, 151, 7), // "setFont"
QT_MOC_LITERAL(16, 159, 4), // "font"
QT_MOC_LITERAL(17, 164, 9), // "setSource"
QT_MOC_LITERAL(18, 174, 4), // "file"
QT_MOC_LITERAL(19, 179, 17), // "doFindTextChanged"
QT_MOC_LITERAL(20, 197, 4), // "text"
QT_MOC_LITERAL(21, 202, 16), // "doFindNextButton"
QT_MOC_LITERAL(22, 219, 20) // "doFindPreviousButton"

    },
    "TextWindowSimple\0windowOpen\0\0rhs\0"
    "doPrintAction\0doSaveAction\0doClearAllAction\0"
    "doWindowClosing\0setTextFormat\0"
    "Qt::TextFormat\0f\0appendText\0s\0setText\0"
    "clear\0setFont\0font\0setSource\0file\0"
    "doFindTextChanged\0text\0doFindNextButton\0"
    "doFindPreviousButton"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TextWindowSimple[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   87,    2, 0x0a /* Public */,
       5,    0,   88,    2, 0x0a /* Public */,
       6,    0,   89,    2, 0x0a /* Public */,
       7,    0,   90,    2, 0x0a /* Public */,
       8,    1,   91,    2, 0x0a /* Public */,
      11,    1,   94,    2, 0x0a /* Public */,
      13,    1,   97,    2, 0x0a /* Public */,
      14,    0,  100,    2, 0x0a /* Public */,
      15,    1,  101,    2, 0x0a /* Public */,
      17,    1,  104,    2, 0x0a /* Public */,
      19,    1,  107,    2, 0x0a /* Public */,
      21,    0,  110,    2, 0x0a /* Public */,
      22,    0,  111,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QFont,   16,
    QMetaType::Void, QMetaType::QString,   18,
    QMetaType::Void, QMetaType::QString,   20,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void TextWindowSimple::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TextWindowSimple *_t = static_cast<TextWindowSimple *>(_o);
        Q_UNUSED(_t)
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
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (TextWindowSimple::*_t)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TextWindowSimple::windowOpen)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject TextWindowSimple::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_TextWindowSimple.data,
      qt_meta_data_TextWindowSimple,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *TextWindowSimple::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TextWindowSimple::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TextWindowSimple.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "Ui_TextWindowSimple"))
        return static_cast< Ui_TextWindowSimple*>(this);
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
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void TextWindowSimple::windowOpen(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
