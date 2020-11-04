/****************************************************************************
** Meta object code from reading C++ file 'FileChooser.h'
**
** Created: Mon Nov 2 11:18:06 2020
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/FileChooser.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FileChooser.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FileChooser[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       4,   44, // properties
       2,   56, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
      41,   38,   12,   12, 0x0a,
      64,   62,   12,   12, 0x0a,
      80,   78,   12,   12, 0x0a,
      98,   94,   12,   12, 0x0a,
     115,   12,   12,   12, 0x08,

 // properties: name, type, flags
     133,  128, 0x0009510b,
     143,  138, 0x0009510b,
     156,  148, 0x0a095103,
     170,  165, 0x01095103,

 // enums: name, flags, count, data
     128, 0x0,    2,   64,
     138, 0x0,    2,   68,

 // enum data: key, value
     178, uint(FileChooser::File),
     183, uint(FileChooser::Directory),
     193, uint(FileChooser::Open),
     198, uint(FileChooser::Save),

       0        // eod
};

static const char qt_meta_stringdata_FileChooser[] = {
    "FileChooser\0\0fileNameChanged(QString)\0"
    "fn\0setFileName(QString)\0m\0setMode(Mode)\0"
    "t\0setType(Type)\0rhs\0setPreview(bool)\0"
    "chooseFile()\0Mode\0mode\0Type\0type\0"
    "QString\0fileName\0bool\0preview\0File\0"
    "Directory\0Open\0Save\0"
};

void FileChooser::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        FileChooser *_t = static_cast<FileChooser *>(_o);
        switch (_id) {
        case 0: _t->fileNameChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->setFileName((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->setMode((*reinterpret_cast< Mode(*)>(_a[1]))); break;
        case 3: _t->setType((*reinterpret_cast< Type(*)>(_a[1]))); break;
        case 4: _t->setPreview((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->chooseFile(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData FileChooser::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject FileChooser::staticMetaObject = {
    { &QHBoxLayout::staticMetaObject, qt_meta_stringdata_FileChooser,
      qt_meta_data_FileChooser, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FileChooser::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FileChooser::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FileChooser::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FileChooser))
        return static_cast<void*>(const_cast< FileChooser*>(this));
    return QHBoxLayout::qt_metacast(_clname);
}

int FileChooser::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QHBoxLayout::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< Mode*>(_v) = mode(); break;
        case 1: *reinterpret_cast< Type*>(_v) = type(); break;
        case 2: *reinterpret_cast< QString*>(_v) = fileName(); break;
        case 3: *reinterpret_cast< bool*>(_v) = preview(); break;
        }
        _id -= 4;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setMode(*reinterpret_cast< Mode*>(_v)); break;
        case 1: setType(*reinterpret_cast< Type*>(_v)); break;
        case 2: setFileName(*reinterpret_cast< QString*>(_v)); break;
        case 3: setPreview(*reinterpret_cast< bool*>(_v)); break;
        }
        _id -= 4;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 4;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void FileChooser::fileNameChanged(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
