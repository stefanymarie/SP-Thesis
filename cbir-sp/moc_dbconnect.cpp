/****************************************************************************
** Meta object code from reading C++ file 'dbconnect.h'
**
** Created: Wed Feb 2 12:35:53 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dbconnect.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dbconnect.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_dbconnect[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      23,   10,   10,   10, 0x0a,
      55,   44,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_dbconnect[] = {
    "dbconnect\0\0connected()\0setupdbConnections()\0"
    "queryImage\0insertImageToDB(QFile&)\0"
};

const QMetaObject dbconnect::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_dbconnect,
      qt_meta_data_dbconnect, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &dbconnect::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *dbconnect::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *dbconnect::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_dbconnect))
        return static_cast<void*>(const_cast< dbconnect*>(this));
    return QDialog::qt_metacast(_clname);
}

int dbconnect::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: connected(); break;
        case 1: setupdbConnections(); break;
        case 2: insertImageToDB((*reinterpret_cast< QFile(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void dbconnect::connected()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
