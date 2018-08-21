/****************************************************************************
** Meta object code from reading C++ file 'CbrPlot.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/CbrPlot.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CbrPlot.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_cbr__CbrPlot_t {
    QByteArrayData data[11];
    char stringdata0[76];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_cbr__CbrPlot_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_cbr__CbrPlot_t qt_meta_stringdata_cbr__CbrPlot = {
    {
QT_MOC_LITERAL(0, 0, 12), // "cbr::CbrPlot"
QT_MOC_LITERAL(1, 13, 7), // "setGrid"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 5), // "level"
QT_MOC_LITERAL(4, 28, 5), // "moved"
QT_MOC_LITERAL(5, 34, 8), // "selected"
QT_MOC_LITERAL(6, 43, 8), // "getIndex"
QT_MOC_LITERAL(7, 52, 15), // "QVector<double>"
QT_MOC_LITERAL(8, 68, 1), // "x"
QT_MOC_LITERAL(9, 70, 1), // "y"
QT_MOC_LITERAL(10, 72, 3) // "pos"

    },
    "cbr::CbrPlot\0setGrid\0\0level\0moved\0"
    "selected\0getIndex\0QVector<double>\0x\0"
    "y\0pos"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_cbr__CbrPlot[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x0a /* Public */,
       1,    0,   42,    2, 0x2a /* Public | MethodCloned */,
       4,    1,   43,    2, 0x0a /* Public */,
       5,    1,   46,    2, 0x0a /* Public */,
       6,    3,   49,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,    2,
    QMetaType::Void, QMetaType::QPolygon,    2,
    QMetaType::Int, 0x80000000 | 7, 0x80000000 | 7, QMetaType::QPoint,    8,    9,   10,

       0        // eod
};

void cbr::CbrPlot::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CbrPlot *_t = static_cast<CbrPlot *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setGrid((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->setGrid(); break;
        case 2: _t->moved((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 3: _t->selected((*reinterpret_cast< const QPolygon(*)>(_a[1]))); break;
        case 4: { int _r = _t->getIndex((*reinterpret_cast< const QVector<double>(*)>(_a[1])),(*reinterpret_cast< const QVector<double>(*)>(_a[2])),(*reinterpret_cast< const QPoint(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<double> >(); break;
            }
            break;
        }
    }
}

const QMetaObject cbr::CbrPlot::staticMetaObject = {
    { &QwtPlot::staticMetaObject, qt_meta_stringdata_cbr__CbrPlot.data,
      qt_meta_data_cbr__CbrPlot,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *cbr::CbrPlot::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *cbr::CbrPlot::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_cbr__CbrPlot.stringdata0))
        return static_cast<void*>(const_cast< CbrPlot*>(this));
    return QwtPlot::qt_metacast(_clname);
}

int cbr::CbrPlot::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QwtPlot::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
