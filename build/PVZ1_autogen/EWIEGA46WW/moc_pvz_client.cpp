/****************************************************************************
** Meta object code from reading C++ file 'pvz_client.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../pvz_client.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pvz_client.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PVZClient_t {
    QByteArrayData data[16];
    char stringdata0[145];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PVZClient_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PVZClient_t qt_meta_stringdata_PVZClient = {
    {
QT_MOC_LITERAL(0, 0, 9), // "PVZClient"
QT_MOC_LITERAL(1, 10, 11), // "CreatePlant"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 4), // "line"
QT_MOC_LITERAL(4, 28, 6), // "column"
QT_MOC_LITERAL(5, 35, 10), // "plant_type"
QT_MOC_LITERAL(6, 46, 3), // "seq"
QT_MOC_LITERAL(7, 50, 7), // "respond"
QT_MOC_LITERAL(8, 58, 12), // "DestroyPlant"
QT_MOC_LITERAL(9, 71, 12), // "CreateZombie"
QT_MOC_LITERAL(10, 84, 11), // "zombie_type"
QT_MOC_LITERAL(11, 96, 10), // "ProduceSun"
QT_MOC_LITERAL(12, 107, 5), // "sun_x"
QT_MOC_LITERAL(13, 113, 9), // "GameStart"
QT_MOC_LITERAL(14, 123, 11), // "CloseWindow"
QT_MOC_LITERAL(15, 135, 9) // "ZombieEnd"

    },
    "PVZClient\0CreatePlant\0\0line\0column\0"
    "plant_type\0seq\0respond\0DestroyPlant\0"
    "CreateZombie\0zombie_type\0ProduceSun\0"
    "sun_x\0GameStart\0CloseWindow\0ZombieEnd"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PVZClient[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    5,   49,    2, 0x06 /* Public */,
       8,    4,   60,    2, 0x06 /* Public */,
       9,    2,   69,    2, 0x06 /* Public */,
      11,    1,   74,    2, 0x06 /* Public */,
      13,    0,   77,    2, 0x06 /* Public */,
      14,    0,   78,    2, 0x06 /* Public */,
      15,    0,   79,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Bool,    3,    4,    5,    6,    7,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Bool,    3,    4,    6,    7,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   10,    3,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PVZClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PVZClient *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->CreatePlant((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< bool(*)>(_a[5]))); break;
        case 1: _t->DestroyPlant((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4]))); break;
        case 2: _t->CreateZombie((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->ProduceSun((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->GameStart(); break;
        case 5: _t->CloseWindow(); break;
        case 6: _t->ZombieEnd(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PVZClient::*)(int , int , int , int , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PVZClient::CreatePlant)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (PVZClient::*)(int , int , int , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PVZClient::DestroyPlant)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (PVZClient::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PVZClient::CreateZombie)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (PVZClient::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PVZClient::ProduceSun)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (PVZClient::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PVZClient::GameStart)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (PVZClient::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PVZClient::CloseWindow)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (PVZClient::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PVZClient::ZombieEnd)) {
                *result = 6;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PVZClient::staticMetaObject = { {
    QMetaObject::SuperData::link<QThread::staticMetaObject>(),
    qt_meta_stringdata_PVZClient.data,
    qt_meta_data_PVZClient,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PVZClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PVZClient::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PVZClient.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int PVZClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
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
void PVZClient::CreatePlant(int _t1, int _t2, int _t3, int _t4, bool _t5)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t5))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PVZClient::DestroyPlant(int _t1, int _t2, int _t3, bool _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void PVZClient::CreateZombie(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void PVZClient::ProduceSun(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void PVZClient::GameStart()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void PVZClient::CloseWindow()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void PVZClient::ZombieEnd()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
