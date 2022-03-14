/****************************************************************************
** Meta object code from reading C++ file 'ConfigWidgetImpl.h'
**
** Created: Thu Mar 10 16:46:41 2022
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/ConfigWidgetImpl.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ConfigWidgetImpl.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ConfigWidgetImpl[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      37,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x05,
      42,   17,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
      68,   17,   17,   17, 0x0a,
      76,   17,   17,   17, 0x0a,
      91,   17,   17,   17, 0x0a,
     108,   17,   17,   17, 0x0a,
     136,   17,   17,   17, 0x0a,
     165,   17,   17,   17, 0x0a,
     182,   17,   17,   17, 0x0a,
     202,   17,   17,   17, 0x0a,
     225,   17,   17,   17, 0x0a,
     248,   17,   17,   17, 0x0a,
     271,   17,   17,   17, 0x0a,
     299,   17,   17,   17, 0x0a,
     327,   17,   17,   17, 0x0a,
     355,   17,   17,   17, 0x0a,
     374,  371,   17,   17, 0x0a,
     413,   17,   17,   17, 0x0a,
     444,  440,   17,   17, 0x0a,
     475,   17,   17,   17, 0x0a,
     497,  495,   17,   17, 0x0a,
     518,   17,   17,   17, 0x0a,
     539,   17,   17,   17, 0x0a,
     561,   17,   17,   17, 0x0a,
     585,   17,   17,   17, 0x0a,
     609,   17,   17,   17, 0x0a,
     628,   17,   17,   17, 0x0a,
     648,   17,   17,   17, 0x0a,
     671,   17,   17,   17, 0x0a,
     693,   17,   17,   17, 0x0a,
     717,   17,   17,   17, 0x0a,
     738,   17,   17,   17, 0x0a,
     759,   17,   17,   17, 0x0a,
     787,   17,   17,   17, 0x0a,
     817,   17,   17,   17, 0x0a,
     838,   17,   17,   17, 0x0a,
     860,   17,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ConfigWidgetImpl[] = {
    "ConfigWidgetImpl\0\0dataDirChanged(QString)\0"
    "outputDirChanged(QString)\0apply()\0"
    "updateWidget()\0updateSettings()\0"
    "dataDirNameChanged(QString)\0"
    "ouputDirNameChanged(QString)\0"
    "doAddRunButton()\0doDeleteRunButton()\0"
    "doAddHistFieldButton()\0doAddAdultSiteButton()\0"
    "doAddTransSiteButton()\0"
    "doHistFieldListMenu(QPoint)\0"
    "doAdultSiteListMenu(QPoint)\0"
    "doTransSiteListMenu(QPoint)\0doApplyButton()\0"
    ",,\0doContextMenuRequested(int,int,QPoint)\0"
    "doCurrentChanged(QWidget*)\0rhs\0"
    "onRelSiteCheckBoxClicked(bool)\0"
    "refreshCurrentTab()\0w\0refreshTab(QWidget*)\0"
    "refreshRunSetupTab()\0refreshRelSiteCombo()\0"
    "refreshLastFieldCombo()\0refreshTransSitesList()\0"
    "refreshHistLists()\0updateMimeFactory()\0"
    "dataDirButtonClicked()\0outDirButtonClicked()\0"
    "sortJuvenileSitesList()\0sortAdultSitesList()\0"
    "sortTransSitesList()\0emitDataDirChanged(QString)\0"
    "emitOutputDirChanged(QString)\0"
    "updateAllDataLists()\0versionComboChanged()\0"
    "refreshSitesTab()\0"
};

void ConfigWidgetImpl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ConfigWidgetImpl *_t = static_cast<ConfigWidgetImpl *>(_o);
        switch (_id) {
        case 0: _t->dataDirChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->outputDirChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->apply(); break;
        case 3: _t->updateWidget(); break;
        case 4: _t->updateSettings(); break;
        case 5: _t->dataDirNameChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->ouputDirNameChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->doAddRunButton(); break;
        case 8: _t->doDeleteRunButton(); break;
        case 9: _t->doAddHistFieldButton(); break;
        case 10: _t->doAddAdultSiteButton(); break;
        case 11: _t->doAddTransSiteButton(); break;
        case 12: _t->doHistFieldListMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 13: _t->doAdultSiteListMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 14: _t->doTransSiteListMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 15: _t->doApplyButton(); break;
        case 16: _t->doContextMenuRequested((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< const QPoint(*)>(_a[3]))); break;
        case 17: _t->doCurrentChanged((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 18: _t->onRelSiteCheckBoxClicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 19: _t->refreshCurrentTab(); break;
        case 20: _t->refreshTab((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 21: _t->refreshRunSetupTab(); break;
        case 22: _t->refreshRelSiteCombo(); break;
        case 23: _t->refreshLastFieldCombo(); break;
        case 24: _t->refreshTransSitesList(); break;
        case 25: _t->refreshHistLists(); break;
        case 26: _t->updateMimeFactory(); break;
        case 27: _t->dataDirButtonClicked(); break;
        case 28: _t->outDirButtonClicked(); break;
        case 29: _t->sortJuvenileSitesList(); break;
        case 30: _t->sortAdultSitesList(); break;
        case 31: _t->sortTransSitesList(); break;
        case 32: _t->emitDataDirChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 33: _t->emitOutputDirChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 34: _t->updateAllDataLists(); break;
        case 35: _t->versionComboChanged(); break;
        case 36: _t->refreshSitesTab(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ConfigWidgetImpl::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ConfigWidgetImpl::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ConfigWidgetImpl,
      qt_meta_data_ConfigWidgetImpl, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ConfigWidgetImpl::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ConfigWidgetImpl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ConfigWidgetImpl::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ConfigWidgetImpl))
        return static_cast<void*>(const_cast< ConfigWidgetImpl*>(this));
    if (!strcmp(_clname, "Ui::ConfigWidget"))
        return static_cast< Ui::ConfigWidget*>(const_cast< ConfigWidgetImpl*>(this));
    return QWidget::qt_metacast(_clname);
}

int ConfigWidgetImpl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 37)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 37;
    }
    return _id;
}

// SIGNAL 0
void ConfigWidgetImpl::dataDirChanged(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ConfigWidgetImpl::outputDirChanged(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
