/****************************************************************************
** Meta object code from reading C++ file 'ResultsManagerImpl.h'
**
** Created: Mon Nov 2 11:22:38 2020
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/ResultsManagerImpl.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ResultsManagerImpl.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ResultsManagerImpl[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      24,   20,   19,   19, 0x0a,
      39,   19,   19,   19, 0x2a,
      50,   19,   19,   19, 0x0a,
      68,   19,   19,   19, 0x08,
     100,   96,   19,   19, 0x08,
     122,   96,   19,   19, 0x08,
     148,   19,   19,   19, 0x08,
     166,   19,   19,   19, 0x08,
     188,   19,   19,   19, 0x08,
     214,   19,   19,   19, 0x08,
     229,   19,   19,   19, 0x08,
     241,   19,   19,   19, 0x08,
     262,   19,   19,   19, 0x08,
     273,   19,   19,   19, 0x08,
     283,   19,   19,   19, 0x08,
     292,   19,   19,   19, 0x08,
     320,   19,   19,   19, 0x08,
     345,   19,   19,   19, 0x08,
     375,   19,   19,   19, 0x08,
     404,   19,   19,   19, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ResultsManagerImpl[] = {
    "ResultsManagerImpl\0\0rhs\0setStale(bool)\0"
    "setStale()\0setGroup(QString)\0"
    "currentTabChanged(QWidget*)\0run\0"
    "updateTtPage(QString)\0updateErrorsPage(QString)\0"
    "summaryPageHome()\0dataSummaryPageHome()\0"
    "outputDirChanged(QString)\0trackPitCode()\0"
    "doCjsData()\0doCovarianceMatrix()\0"
    "doTTData()\0doPrint()\0doSave()\0"
    "onTrackerDetailChecked(int)\0"
    "onShowLambdaChecked(int)\0"
    "onShowOneTableCjsChecked(int)\0"
    "doSummaryAnchorClicked(QUrl)\0"
    "doDataAnchorClicked(QUrl)\0"
};

void ResultsManagerImpl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ResultsManagerImpl *_t = static_cast<ResultsManagerImpl *>(_o);
        switch (_id) {
        case 0: _t->setStale((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->setStale(); break;
        case 2: _t->setGroup((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->currentTabChanged((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 4: _t->updateTtPage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->updateErrorsPage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->summaryPageHome(); break;
        case 7: _t->dataSummaryPageHome(); break;
        case 8: _t->outputDirChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 9: _t->trackPitCode(); break;
        case 10: _t->doCjsData(); break;
        case 11: _t->doCovarianceMatrix(); break;
        case 12: _t->doTTData(); break;
        case 13: _t->doPrint(); break;
        case 14: _t->doSave(); break;
        case 15: _t->onTrackerDetailChecked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->onShowLambdaChecked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: _t->onShowOneTableCjsChecked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: _t->doSummaryAnchorClicked((*reinterpret_cast< const QUrl(*)>(_a[1]))); break;
        case 19: _t->doDataAnchorClicked((*reinterpret_cast< const QUrl(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ResultsManagerImpl::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ResultsManagerImpl::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_ResultsManagerImpl,
      qt_meta_data_ResultsManagerImpl, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ResultsManagerImpl::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ResultsManagerImpl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ResultsManagerImpl::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ResultsManagerImpl))
        return static_cast<void*>(const_cast< ResultsManagerImpl*>(this));
    if (!strcmp(_clname, "Ui::ResultManager"))
        return static_cast< Ui::ResultManager*>(const_cast< ResultsManagerImpl*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int ResultsManagerImpl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
