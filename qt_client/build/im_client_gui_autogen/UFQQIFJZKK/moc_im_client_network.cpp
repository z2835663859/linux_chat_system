/****************************************************************************
** Meta object code from reading C++ file 'im_client_network.hpp'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/network/im_client_network.hpp"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'im_client_network.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSIMClientNetworkENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSIMClientNetworkENDCLASS = QtMocHelpers::stringData(
    "IMClientNetwork",
    "connected",
    "",
    "disconnected",
    "connection_error",
    "error",
    "login_success",
    "uint32_t",
    "user_id",
    "username",
    "login_failed",
    "register_success",
    "register_failed",
    "logout_success",
    "message_received",
    "from_user_id",
    "from_username",
    "text",
    "group_message_received",
    "group_id",
    "group_created",
    "group_name",
    "group_joined",
    "group_left",
    "groups_list_received",
    "json_list",
    "group_members_received",
    "json_members",
    "notify",
    "message",
    "heartbeat_response",
    "on_connected",
    "on_disconnected",
    "on_error",
    "QAbstractSocket::SocketError",
    "on_ready_read"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSIMClientNetworkENDCLASS_t {
    uint offsetsAndSizes[72];
    char stringdata0[16];
    char stringdata1[10];
    char stringdata2[1];
    char stringdata3[13];
    char stringdata4[17];
    char stringdata5[6];
    char stringdata6[14];
    char stringdata7[9];
    char stringdata8[8];
    char stringdata9[9];
    char stringdata10[13];
    char stringdata11[17];
    char stringdata12[16];
    char stringdata13[15];
    char stringdata14[17];
    char stringdata15[13];
    char stringdata16[14];
    char stringdata17[5];
    char stringdata18[23];
    char stringdata19[9];
    char stringdata20[14];
    char stringdata21[11];
    char stringdata22[13];
    char stringdata23[11];
    char stringdata24[21];
    char stringdata25[10];
    char stringdata26[23];
    char stringdata27[13];
    char stringdata28[7];
    char stringdata29[8];
    char stringdata30[19];
    char stringdata31[13];
    char stringdata32[16];
    char stringdata33[9];
    char stringdata34[29];
    char stringdata35[14];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSIMClientNetworkENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSIMClientNetworkENDCLASS_t qt_meta_stringdata_CLASSIMClientNetworkENDCLASS = {
    {
        QT_MOC_LITERAL(0, 15),  // "IMClientNetwork"
        QT_MOC_LITERAL(16, 9),  // "connected"
        QT_MOC_LITERAL(26, 0),  // ""
        QT_MOC_LITERAL(27, 12),  // "disconnected"
        QT_MOC_LITERAL(40, 16),  // "connection_error"
        QT_MOC_LITERAL(57, 5),  // "error"
        QT_MOC_LITERAL(63, 13),  // "login_success"
        QT_MOC_LITERAL(77, 8),  // "uint32_t"
        QT_MOC_LITERAL(86, 7),  // "user_id"
        QT_MOC_LITERAL(94, 8),  // "username"
        QT_MOC_LITERAL(103, 12),  // "login_failed"
        QT_MOC_LITERAL(116, 16),  // "register_success"
        QT_MOC_LITERAL(133, 15),  // "register_failed"
        QT_MOC_LITERAL(149, 14),  // "logout_success"
        QT_MOC_LITERAL(164, 16),  // "message_received"
        QT_MOC_LITERAL(181, 12),  // "from_user_id"
        QT_MOC_LITERAL(194, 13),  // "from_username"
        QT_MOC_LITERAL(208, 4),  // "text"
        QT_MOC_LITERAL(213, 22),  // "group_message_received"
        QT_MOC_LITERAL(236, 8),  // "group_id"
        QT_MOC_LITERAL(245, 13),  // "group_created"
        QT_MOC_LITERAL(259, 10),  // "group_name"
        QT_MOC_LITERAL(270, 12),  // "group_joined"
        QT_MOC_LITERAL(283, 10),  // "group_left"
        QT_MOC_LITERAL(294, 20),  // "groups_list_received"
        QT_MOC_LITERAL(315, 9),  // "json_list"
        QT_MOC_LITERAL(325, 22),  // "group_members_received"
        QT_MOC_LITERAL(348, 12),  // "json_members"
        QT_MOC_LITERAL(361, 6),  // "notify"
        QT_MOC_LITERAL(368, 7),  // "message"
        QT_MOC_LITERAL(376, 18),  // "heartbeat_response"
        QT_MOC_LITERAL(395, 12),  // "on_connected"
        QT_MOC_LITERAL(408, 15),  // "on_disconnected"
        QT_MOC_LITERAL(424, 8),  // "on_error"
        QT_MOC_LITERAL(433, 28),  // "QAbstractSocket::SocketError"
        QT_MOC_LITERAL(462, 13)   // "on_ready_read"
    },
    "IMClientNetwork",
    "connected",
    "",
    "disconnected",
    "connection_error",
    "error",
    "login_success",
    "uint32_t",
    "user_id",
    "username",
    "login_failed",
    "register_success",
    "register_failed",
    "logout_success",
    "message_received",
    "from_user_id",
    "from_username",
    "text",
    "group_message_received",
    "group_id",
    "group_created",
    "group_name",
    "group_joined",
    "group_left",
    "groups_list_received",
    "json_list",
    "group_members_received",
    "json_members",
    "notify",
    "message",
    "heartbeat_response",
    "on_connected",
    "on_disconnected",
    "on_error",
    "QAbstractSocket::SocketError",
    "on_ready_read"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSIMClientNetworkENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
      21,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      17,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  140,    2, 0x06,    1 /* Public */,
       3,    0,  141,    2, 0x06,    2 /* Public */,
       4,    1,  142,    2, 0x06,    3 /* Public */,
       6,    2,  145,    2, 0x06,    5 /* Public */,
      10,    1,  150,    2, 0x06,    8 /* Public */,
      11,    0,  153,    2, 0x06,   10 /* Public */,
      12,    1,  154,    2, 0x06,   11 /* Public */,
      13,    0,  157,    2, 0x06,   13 /* Public */,
      14,    3,  158,    2, 0x06,   14 /* Public */,
      18,    4,  165,    2, 0x06,   18 /* Public */,
      20,    2,  174,    2, 0x06,   23 /* Public */,
      22,    1,  179,    2, 0x06,   26 /* Public */,
      23,    1,  182,    2, 0x06,   28 /* Public */,
      24,    1,  185,    2, 0x06,   30 /* Public */,
      26,    2,  188,    2, 0x06,   32 /* Public */,
      28,    1,  193,    2, 0x06,   35 /* Public */,
      30,    0,  196,    2, 0x06,   37 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      31,    0,  197,    2, 0x08,   38 /* Private */,
      32,    0,  198,    2, 0x08,   39 /* Private */,
      33,    1,  199,    2, 0x08,   40 /* Private */,
      35,    0,  202,    2, 0x08,   42 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, 0x80000000 | 7, QMetaType::QString,    8,    9,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7, QMetaType::QString, QMetaType::QString,   15,   16,   17,
    QMetaType::Void, 0x80000000 | 7, 0x80000000 | 7, QMetaType::QString, QMetaType::QString,   19,   15,   16,   17,
    QMetaType::Void, 0x80000000 | 7, QMetaType::QString,   19,   21,
    QMetaType::Void, 0x80000000 | 7,   19,
    QMetaType::Void, 0x80000000 | 7,   19,
    QMetaType::Void, QMetaType::QString,   25,
    QMetaType::Void, 0x80000000 | 7, QMetaType::QString,   19,   27,
    QMetaType::Void, QMetaType::QString,   29,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 34,    5,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject IMClientNetwork::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSIMClientNetworkENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSIMClientNetworkENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSIMClientNetworkENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<IMClientNetwork, std::true_type>,
        // method 'connected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'disconnected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'connection_error'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'login_success'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<uint32_t, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'login_failed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'register_success'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'register_failed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'logout_success'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'message_received'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<uint32_t, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'group_message_received'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<uint32_t, std::false_type>,
        QtPrivate::TypeAndForceComplete<uint32_t, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'group_created'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<uint32_t, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'group_joined'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<uint32_t, std::false_type>,
        // method 'group_left'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<uint32_t, std::false_type>,
        // method 'groups_list_received'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'group_members_received'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<uint32_t, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'notify'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'heartbeat_response'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_connected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_disconnected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_error'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QAbstractSocket::SocketError, std::false_type>,
        // method 'on_ready_read'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void IMClientNetwork::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<IMClientNetwork *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->connected(); break;
        case 1: _t->disconnected(); break;
        case 2: _t->connection_error((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->login_success((*reinterpret_cast< std::add_pointer_t<uint32_t>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 4: _t->login_failed((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 5: _t->register_success(); break;
        case 6: _t->register_failed((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 7: _t->logout_success(); break;
        case 8: _t->message_received((*reinterpret_cast< std::add_pointer_t<uint32_t>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3]))); break;
        case 9: _t->group_message_received((*reinterpret_cast< std::add_pointer_t<uint32_t>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<uint32_t>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[4]))); break;
        case 10: _t->group_created((*reinterpret_cast< std::add_pointer_t<uint32_t>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 11: _t->group_joined((*reinterpret_cast< std::add_pointer_t<uint32_t>>(_a[1]))); break;
        case 12: _t->group_left((*reinterpret_cast< std::add_pointer_t<uint32_t>>(_a[1]))); break;
        case 13: _t->groups_list_received((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 14: _t->group_members_received((*reinterpret_cast< std::add_pointer_t<uint32_t>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 15: _t->notify((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 16: _t->heartbeat_response(); break;
        case 17: _t->on_connected(); break;
        case 18: _t->on_disconnected(); break;
        case 19: _t->on_error((*reinterpret_cast< std::add_pointer_t<QAbstractSocket::SocketError>>(_a[1]))); break;
        case 20: _t->on_ready_read(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 19:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (IMClientNetwork::*)();
            if (_t _q_method = &IMClientNetwork::connected; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (IMClientNetwork::*)();
            if (_t _q_method = &IMClientNetwork::disconnected; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (IMClientNetwork::*)(const QString & );
            if (_t _q_method = &IMClientNetwork::connection_error; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (IMClientNetwork::*)(uint32_t , const QString & );
            if (_t _q_method = &IMClientNetwork::login_success; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (IMClientNetwork::*)(const QString & );
            if (_t _q_method = &IMClientNetwork::login_failed; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (IMClientNetwork::*)();
            if (_t _q_method = &IMClientNetwork::register_success; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (IMClientNetwork::*)(const QString & );
            if (_t _q_method = &IMClientNetwork::register_failed; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (IMClientNetwork::*)();
            if (_t _q_method = &IMClientNetwork::logout_success; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (IMClientNetwork::*)(uint32_t , const QString & , const QString & );
            if (_t _q_method = &IMClientNetwork::message_received; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (IMClientNetwork::*)(uint32_t , uint32_t , const QString & , const QString & );
            if (_t _q_method = &IMClientNetwork::group_message_received; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (IMClientNetwork::*)(uint32_t , const QString & );
            if (_t _q_method = &IMClientNetwork::group_created; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (IMClientNetwork::*)(uint32_t );
            if (_t _q_method = &IMClientNetwork::group_joined; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (IMClientNetwork::*)(uint32_t );
            if (_t _q_method = &IMClientNetwork::group_left; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (IMClientNetwork::*)(const QString & );
            if (_t _q_method = &IMClientNetwork::groups_list_received; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (IMClientNetwork::*)(uint32_t , const QString & );
            if (_t _q_method = &IMClientNetwork::group_members_received; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 14;
                return;
            }
        }
        {
            using _t = void (IMClientNetwork::*)(const QString & );
            if (_t _q_method = &IMClientNetwork::notify; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 15;
                return;
            }
        }
        {
            using _t = void (IMClientNetwork::*)();
            if (_t _q_method = &IMClientNetwork::heartbeat_response; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 16;
                return;
            }
        }
    }
}

const QMetaObject *IMClientNetwork::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *IMClientNetwork::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSIMClientNetworkENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int IMClientNetwork::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    }
    return _id;
}

// SIGNAL 0
void IMClientNetwork::connected()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void IMClientNetwork::disconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void IMClientNetwork::connection_error(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void IMClientNetwork::login_success(uint32_t _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void IMClientNetwork::login_failed(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void IMClientNetwork::register_success()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void IMClientNetwork::register_failed(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void IMClientNetwork::logout_success()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void IMClientNetwork::message_received(uint32_t _t1, const QString & _t2, const QString & _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void IMClientNetwork::group_message_received(uint32_t _t1, uint32_t _t2, const QString & _t3, const QString & _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void IMClientNetwork::group_created(uint32_t _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void IMClientNetwork::group_joined(uint32_t _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void IMClientNetwork::group_left(uint32_t _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void IMClientNetwork::groups_list_received(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void IMClientNetwork::group_members_received(uint32_t _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void IMClientNetwork::notify(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void IMClientNetwork::heartbeat_response()
{
    QMetaObject::activate(this, &staticMetaObject, 16, nullptr);
}
QT_WARNING_POP
