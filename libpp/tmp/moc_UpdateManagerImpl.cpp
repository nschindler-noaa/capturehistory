/****************************************************************************
** Meta object code from reading C++ file 'UpdateManagerImpl.h'
**
** Created: Thu Mar 10 16:46:46 2022
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/UpdateManagerImpl.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'UpdateManagerImpl.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_UpdateManagerImpl[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      26,   19,   18,   18, 0x05,
      66,   18,   18,   18, 0x05,

 // slots: signature, parameters, type, tag, flags
      87,   18,   18,   18, 0x0a,
      97,   18,   18,   18, 0x08,
     130,  114,   18,   18, 0x08,
     175,  160,   18,   18, 0x08,
     225,  204,   18,   18, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_UpdateManagerImpl[] = {
    "UpdateManagerImpl\0\0status\0"
    "updateStatus(UpdateManagerImpl::Status)\0"
    "sitesConfigUpdated()\0refresh()\0"
    "doUpdateButton()\0requestId,error\0"
    "httpRequestFinished(int,bool)\0"
    "responseHeader\0readResponseHeader(QString&)\0"
    "bytesRead,totalBytes\0"
    "updateDataReadProgress(int,int)\0"
};

void UpdateManagerImpl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        UpdateManagerImpl *_t = static_cast<UpdateManagerImpl *>(_o);
        switch (_id) {
        case 0: _t->updateStatus((*reinterpret_cast< UpdateManagerImpl::Status(*)>(_a[1]))); break;
        case 1: _t->sitesConfigUpdated(); break;
        case 2: _t->refresh(); break;
        case 3: _t->doUpdateButton(); break;
        case 4: _t->httpRequestFinished((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 5: _t->readResponseHeader((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->updateDataReadProgress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData UpdateManagerImpl::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject UpdateManagerImpl::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_UpdateManagerImpl,
      qt_meta_data_UpdateManagerImpl, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &UpdateManagerImpl::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *UpdateManagerImpl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *UpdateManagerImpl::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UpdateManagerImpl))
        return static_cast<void*>(const_cast< UpdateManagerImpl*>(this));
    if (!strcmp(_clname, "Ui::UpdateManager"))
        return static_cast< Ui::UpdateManager*>(const_cast< UpdateManagerImpl*>(this));
    return QDialog::qt_metacast(_clname);
}

int UpdateManagerImpl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void UpdateManagerImpl::updateStatus(UpdateManagerImpl::Status _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void UpdateManagerImpl::sitesConfigUpdated()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
