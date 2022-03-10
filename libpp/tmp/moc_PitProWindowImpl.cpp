/****************************************************************************
** Meta object code from reading C++ file 'PitProWindowImpl.h'
**
** Created: Wed Mar 9 17:06:54 2022
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/PitProWindowImpl.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PitProWindowImpl.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PitProWindowImpl[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      22,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x0a,
      46,   17,   17,   17, 0x0a,
      74,   17,   17,   17, 0x0a,
     101,   17,   17,   17, 0x0a,
     127,   17,   17,   17, 0x0a,
     141,   17,   17,   17, 0x0a,
     156,   17,   17,   17, 0x0a,
     183,   17,   17,   17, 0x0a,
     210,   17,   17,   17, 0x0a,
     232,   17,   17,   17, 0x0a,
     252,   17,   17,   17, 0x0a,
     278,   17,   17,   17, 0x0a,
     299,   17,   17,   17, 0x0a,
     318,   17,   17,   17, 0x0a,
     330,   17,   17,   17, 0x0a,
     359,  352,   17,   17, 0x0a,
     403,   17,   17,   17, 0x0a,
     431,   17,   17,   17, 0x0a,
     452,   17,   17,   17, 0x0a,
     476,   17,   17,   17, 0x0a,
     496,   17,   17,   17, 0x0a,
     516,   17,   17,   17, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_PitProWindowImpl[] = {
    "PitProWindowImpl\0\0doLoadConfigurationAction()\0"
    "doSaveConfigurationAction()\0"
    "doSaveRunConfigurationAs()\0"
    "doRestoreDefaultsAction()\0doRunAction()\0"
    "doExitAction()\0doShowOutputWindowAction()\0"
    "doShowConfigWindowAction()\0"
    "doShowSummaryAction()\0doCancelRunAction()\0"
    "doShowDataManagerAction()\0"
    "doShowManualAction()\0doShowInfoAction()\0"
    "cancelRun()\0refreshConfigWindow()\0"
    "status\0updateStatusSlot(UpdateManagerImpl::Status)\0"
    "doShowUpdateManagerAction()\0"
    "refreshSitesConfig()\0doDataConverterAction()\0"
    "onEditSitesConfig()\0onCheckForUpdates()\0"
    "on_actionData_converter_triggered()\0"
};

void PitProWindowImpl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PitProWindowImpl *_t = static_cast<PitProWindowImpl *>(_o);
        switch (_id) {
        case 0: _t->doLoadConfigurationAction(); break;
        case 1: _t->doSaveConfigurationAction(); break;
        case 2: _t->doSaveRunConfigurationAs(); break;
        case 3: _t->doRestoreDefaultsAction(); break;
        case 4: _t->doRunAction(); break;
        case 5: _t->doExitAction(); break;
        case 6: _t->doShowOutputWindowAction(); break;
        case 7: _t->doShowConfigWindowAction(); break;
        case 8: _t->doShowSummaryAction(); break;
        case 9: _t->doCancelRunAction(); break;
        case 10: _t->doShowDataManagerAction(); break;
        case 11: _t->doShowManualAction(); break;
        case 12: _t->doShowInfoAction(); break;
        case 13: _t->cancelRun(); break;
        case 14: _t->refreshConfigWindow(); break;
        case 15: _t->updateStatusSlot((*reinterpret_cast< UpdateManagerImpl::Status(*)>(_a[1]))); break;
        case 16: _t->doShowUpdateManagerAction(); break;
        case 17: _t->refreshSitesConfig(); break;
        case 18: _t->doDataConverterAction(); break;
        case 19: _t->onEditSitesConfig(); break;
        case 20: _t->onCheckForUpdates(); break;
        case 21: _t->on_actionData_converter_triggered(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData PitProWindowImpl::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject PitProWindowImpl::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_PitProWindowImpl,
      qt_meta_data_PitProWindowImpl, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PitProWindowImpl::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PitProWindowImpl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PitProWindowImpl::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PitProWindowImpl))
        return static_cast<void*>(const_cast< PitProWindowImpl*>(this));
    if (!strcmp(_clname, "Ui::PitProWindow"))
        return static_cast< Ui::PitProWindow*>(const_cast< PitProWindowImpl*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int PitProWindowImpl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 22)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 22;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
