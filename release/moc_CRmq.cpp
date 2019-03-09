/****************************************************************************
** Meta object code from reading C++ file 'CRmq.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../CRmq.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CRmq.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CRmq_t {
    QByteArrayData data[8];
    char stringdata0[72];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CRmq_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CRmq_t qt_meta_stringdata_CRmq = {
    {
QT_MOC_LITERAL(0, 0, 4), // "CRmq"
QT_MOC_LITERAL(1, 5, 8), // "send_fin"
QT_MOC_LITERAL(2, 14, 0), // ""
QT_MOC_LITERAL(3, 15, 12), // "send_msg_str"
QT_MOC_LITERAL(4, 28, 9), // "st_m_str&"
QT_MOC_LITERAL(5, 38, 14), // "send_msg_cpack"
QT_MOC_LITERAL(6, 53, 11), // "st_m_cpack&"
QT_MOC_LITERAL(7, 65, 6) // "th_run"

    },
    "CRmq\0send_fin\0\0send_msg_str\0st_m_str&\0"
    "send_msg_cpack\0st_m_cpack&\0th_run"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CRmq[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       3,    1,   35,    2, 0x06 /* Public */,
       5,    1,   38,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   41,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void, 0x80000000 | 6,    2,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void CRmq::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CRmq *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->send_fin(); break;
        case 1: _t->send_msg_str((*reinterpret_cast< st_m_str(*)>(_a[1]))); break;
        case 2: _t->send_msg_cpack((*reinterpret_cast< st_m_cpack(*)>(_a[1]))); break;
        case 3: _t->th_run(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CRmq::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CRmq::send_fin)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CRmq::*)(st_m_str & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CRmq::send_msg_str)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (CRmq::*)(st_m_cpack & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CRmq::send_msg_cpack)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CRmq::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_CRmq.data,
    qt_meta_data_CRmq,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CRmq::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CRmq::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CRmq.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int CRmq::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void CRmq::send_fin()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void CRmq::send_msg_str(st_m_str & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CRmq::send_msg_cpack(st_m_cpack & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
