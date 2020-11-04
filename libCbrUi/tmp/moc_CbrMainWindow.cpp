/****************************************************************************
** Meta object code from reading C++ file 'CbrMainWindow.h'
**
** Created: Mon Nov 2 14:55:13 2020
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/CbrMainWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CbrMainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_cbr__CbrMainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      30,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x05,
      48,   19,   19,   19, 0x05,
      82,   19,   19,   19, 0x05,

 // slots: signature, parameters, type, tag, flags
     114,   19,   19,   19, 0x09,
     130,   19,   19,   19, 0x09,
     148,   19,   19,   19, 0x09,
     185,  169,   19,   19, 0x09,
     209,  205,   19,   19, 0x09,
     230,  205,   19,   19, 0x09,
     259,  205,   19,   19, 0x09,
     279,  205,   19,   19, 0x09,
     301,   19,   19,   19, 0x09,
     320,  313,   19,   19, 0x09,
     357,   19,   19,   19, 0x09,
     371,   19,   19,   19, 0x09,
     386,   19,   19,   19, 0x09,
     403,   19,   19,   19, 0x09,
     419,   19,   19,   19, 0x09,
     451,  442,   19,   19, 0x09,
     493,  205,   19,   19, 0x09,
     510,  205,   19,   19, 0x09,
     523,  205,   19,   19, 0x09,
     536,  205,   19,   19, 0x09,
     550,   19,   19,   19, 0x09,
     562,   19,   19,   19, 0x09,
     598,   19,   19,   19, 0x09,
     626,   19,   19,   19, 0x09,
     656,   19,   19,   19, 0x09,
     690,   19,   19,   19, 0x09,
     710,   19,   19,   19, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_cbr__CbrMainWindow[] = {
    "cbr::CbrMainWindow\0\0navItemClicked(QModelIndex)\0"
    "navItemDoubleClicked(QModelIndex)\0"
    "navContextMenuRequested(QPoint)\0"
    "onRunComplete()\0onRunTerminated()\0"
    "onProgressCanceled()\0percentComplete\0"
    "setRunProgress(int)\0msg\0onRunStatus(QString)\0"
    "onRunProgressStatus(QString)\0"
    "onRunError(QString)\0onRunWarning(QString)\0"
    "onRunBusy()\0subWin\0"
    "onSubWindowActivated(QMdiSubWindow*)\0"
    "onHelpAbout()\0doActionSave()\0"
    "doActionSaveAs()\0doActionPrint()\0"
    "doActionPrintPreview()\0msg,type\0"
    "out(QString,OutputDockWidget::OutputType)\0"
    "heading(QString)\0out(QString)\0"
    "err(QString)\0warn(QString)\0updateNav()\0"
    "onNavItemDoubleClicked(QModelIndex)\0"
    "onNavItemDoubleClicked(int)\0"
    "onNavItemClicked(QModelIndex)\0"
    "onNavContextMenuRequested(QPoint)\0"
    "cascadeSubWindows()\0onCheckForUpdates()\0"
};

void cbr::CbrMainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CbrMainWindow *_t = static_cast<CbrMainWindow *>(_o);
        switch (_id) {
        case 0: _t->navItemClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 1: _t->navItemDoubleClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 2: _t->navContextMenuRequested((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 3: _t->onRunComplete(); break;
        case 4: _t->onRunTerminated(); break;
        case 5: _t->onProgressCanceled(); break;
        case 6: _t->setRunProgress((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->onRunStatus((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: _t->onRunProgressStatus((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 9: _t->onRunError((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 10: _t->onRunWarning((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 11: _t->onRunBusy(); break;
        case 12: _t->onSubWindowActivated((*reinterpret_cast< QMdiSubWindow*(*)>(_a[1]))); break;
        case 13: _t->onHelpAbout(); break;
        case 14: _t->doActionSave(); break;
        case 15: _t->doActionSaveAs(); break;
        case 16: _t->doActionPrint(); break;
        case 17: _t->doActionPrintPreview(); break;
        case 18: _t->out((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< OutputDockWidget::OutputType(*)>(_a[2]))); break;
        case 19: _t->heading((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 20: _t->out((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 21: _t->err((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 22: _t->warn((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 23: _t->updateNav(); break;
        case 24: _t->onNavItemDoubleClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 25: _t->onNavItemDoubleClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 26: _t->onNavItemClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 27: _t->onNavContextMenuRequested((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 28: _t->cascadeSubWindows(); break;
        case 29: _t->onCheckForUpdates(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData cbr::CbrMainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject cbr::CbrMainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_cbr__CbrMainWindow,
      qt_meta_data_cbr__CbrMainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &cbr::CbrMainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *cbr::CbrMainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *cbr::CbrMainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_cbr__CbrMainWindow))
        return static_cast<void*>(const_cast< CbrMainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int cbr::CbrMainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 30)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 30;
    }
    return _id;
}

// SIGNAL 0
void cbr::CbrMainWindow::navItemClicked(const QModelIndex & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void cbr::CbrMainWindow::navItemDoubleClicked(const QModelIndex & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void cbr::CbrMainWindow::navContextMenuRequested(const QPoint & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
