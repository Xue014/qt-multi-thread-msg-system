/****************************************************************************
** Meta object code from reading C++ file 'oneuser.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../oneuser.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'oneuser.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Oneuser_t {
    QByteArrayData data[13];
    char stringdata0[117];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Oneuser_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Oneuser_t qt_meta_stringdata_Oneuser = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Oneuser"
QT_MOC_LITERAL(1, 8, 6), // "sendok"
QT_MOC_LITERAL(2, 15, 0), // ""
QT_MOC_LITERAL(3, 16, 12), // "Mainrecemess"
QT_MOC_LITERAL(4, 29, 12), // "FmessageData"
QT_MOC_LITERAL(5, 42, 12), // "Mainrecefile"
QT_MOC_LITERAL(6, 55, 11), // "onlineUsign"
QT_MOC_LITERAL(7, 67, 5), // "Sendm"
QT_MOC_LITERAL(8, 73, 4), // "mess"
QT_MOC_LITERAL(9, 78, 8), // "sendfile"
QT_MOC_LITERAL(10, 87, 4), // "path"
QT_MOC_LITERAL(11, 92, 6), // "ReceID"
QT_MOC_LITERAL(12, 99, 17) // "currentReceiverId"

    },
    "Oneuser\0sendok\0\0Mainrecemess\0FmessageData\0"
    "Mainrecefile\0onlineUsign\0Sendm\0mess\0"
    "sendfile\0path\0ReceID\0currentReceiverId"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Oneuser[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,
       3,    1,   50,    2, 0x06 /* Public */,
       5,    1,   53,    2, 0x06 /* Public */,
       6,    1,   56,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   59,    2, 0x0a /* Public */,
       9,    1,   62,    2, 0x0a /* Public */,
      11,    1,   65,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,    4,
    QMetaType::Void, QMetaType::QByteArray,    4,
    QMetaType::Void, QMetaType::QByteArray,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, QMetaType::QString,   12,

       0        // eod
};

void Oneuser::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Oneuser *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendok(); break;
        case 1: _t->Mainrecemess((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 2: _t->Mainrecefile((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 3: _t->onlineUsign((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 4: _t->Sendm((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->sendfile((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->ReceID((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Oneuser::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Oneuser::sendok)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Oneuser::*)(QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Oneuser::Mainrecemess)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Oneuser::*)(QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Oneuser::Mainrecefile)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Oneuser::*)(QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Oneuser::onlineUsign)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Oneuser::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Oneuser.data,
    qt_meta_data_Oneuser,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Oneuser::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Oneuser::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Oneuser.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Oneuser::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void Oneuser::sendok()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Oneuser::Mainrecemess(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Oneuser::Mainrecefile(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Oneuser::onlineUsign(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
