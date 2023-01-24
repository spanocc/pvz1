/****************************************************************************
** Meta object code from reading C++ file 'shooter.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../shooter.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'shooter.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Shooter_t {
    QByteArrayData data[6];
    char stringdata0[50];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Shooter_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Shooter_t qt_meta_stringdata_Shooter = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Shooter"
QT_MOC_LITERAL(1, 8, 13), // "ProduceBullet"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 3), // "pos"
QT_MOC_LITERAL(4, 27, 10), // "BulletType"
QT_MOC_LITERAL(5, 38, 11) // "bullet_type"

    },
    "Shooter\0ProduceBullet\0\0pos\0BulletType\0"
    "bullet_type"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Shooter[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QPoint, 0x80000000 | 4,    3,    5,

       0        // eod
};

void Shooter::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Shooter *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ProduceBullet((*reinterpret_cast< const QPoint(*)>(_a[1])),(*reinterpret_cast< BulletType(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Shooter::*)(const QPoint & , BulletType );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Shooter::ProduceBullet)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Shooter::staticMetaObject = { {
    QMetaObject::SuperData::link<Plant::staticMetaObject>(),
    qt_meta_stringdata_Shooter.data,
    qt_meta_data_Shooter,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Shooter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Shooter::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Shooter.stringdata0))
        return static_cast<void*>(this);
    return Plant::qt_metacast(_clname);
}

int Shooter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Plant::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void Shooter::ProduceBullet(const QPoint & _t1, BulletType _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
