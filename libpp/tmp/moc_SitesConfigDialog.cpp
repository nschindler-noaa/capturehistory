/****************************************************************************
** Meta object code from reading C++ file 'SitesConfigDialog.h'
**
** Created: Thu Mar 10 16:46:39 2022
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/SitesConfigDialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SitesConfigDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SitesConfigDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x05,

 // slots: signature, parameters, type, tag, flags
      39,   18,   18,   18, 0x0a,
      54,   18,   18,   18, 0x0a,
      75,   18,   18,   18, 0x08,
      98,   18,   18,   18, 0x08,
     108,   18,   18,   18, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SitesConfigDialog[] = {
    "SitesConfigDialog\0\0siteConfigChanged()\0"
    "updateDialog()\0refreshSitesConfig()\0"
    "browseForSitesConfig()\0doApply()\0"
    "checkApplyButtonState()\0"
};

void SitesConfigDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SitesConfigDialog *_t = static_cast<SitesConfigDialog *>(_o);
        switch (_id) {
        case 0: _t->siteConfigChanged(); break;
        case 1: _t->updateDialog(); break;
        case 2: _t->refreshSitesConfig(); break;
        case 3: _t->browseForSitesConfig(); break;
        case 4: _t->doApply(); break;
        case 5: _t->checkApplyButtonState(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData SitesConfigDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SitesConfigDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_SitesConfigDialog,
      qt_meta_data_SitesConfigDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SitesConfigDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SitesConfigDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SitesConfigDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SitesConfigDialog))
        return static_cast<void*>(const_cast< SitesConfigDialog*>(this));
    if (!strcmp(_clname, "Ui::SitesConfigDialog"))
        return static_cast< Ui::SitesConfigDialog*>(const_cast< SitesConfigDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int SitesConfigDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void SitesConfigDialog::siteConfigChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
