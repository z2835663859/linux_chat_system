/****************************************************************************
** Meta object code from reading C++ file 'main_window.hpp'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/ui/main_window.hpp"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'main_window.hpp' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSMainWindowENDCLASS = QtMocHelpers::stringData(
    "MainWindow",
    "on_connected",
    "",
    "on_disconnected",
    "on_connection_error",
    "error",
    "on_login_success",
    "uint32_t",
    "user_id",
    "username",
    "on_login_failed",
    "on_message_received",
    "from_user_id",
    "from_username",
    "text",
    "on_group_message_received",
    "group_id",
    "on_group_created",
    "group_name",
    "on_group_joined",
    "on_groups_list_received",
    "json_list",
    "on_notify",
    "message",
    "on_login_clicked",
    "on_register_clicked",
    "on_switch_to_register_clicked",
    "on_switch_to_login_clicked",
    "on_send_clicked",
    "on_create_group_clicked",
    "on_join_group_clicked",
    "on_user_selected",
    "QModelIndex",
    "index",
    "on_group_selected",
    "on_message_text_changed",
    "on_heartbeat_timeout"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t {
    uint offsetsAndSizes[74];
    char stringdata0[11];
    char stringdata1[13];
    char stringdata2[1];
    char stringdata3[16];
    char stringdata4[20];
    char stringdata5[6];
    char stringdata6[17];
    char stringdata7[9];
    char stringdata8[8];
    char stringdata9[9];
    char stringdata10[16];
    char stringdata11[20];
    char stringdata12[13];
    char stringdata13[14];
    char stringdata14[5];
    char stringdata15[26];
    char stringdata16[9];
    char stringdata17[17];
    char stringdata18[11];
    char stringdata19[16];
    char stringdata20[24];
    char stringdata21[10];
    char stringdata22[10];
    char stringdata23[8];
    char stringdata24[17];
    char stringdata25[20];
    char stringdata26[30];
    char stringdata27[27];
    char stringdata28[16];
    char stringdata29[24];
    char stringdata30[22];
    char stringdata31[17];
    char stringdata32[12];
    char stringdata33[6];
    char stringdata34[18];
    char stringdata35[24];
    char stringdata36[21];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSMainWindowENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSMainWindowENDCLASS_t qt_meta_stringdata_CLASSMainWindowENDCLASS = {
    {
        QT_MOC_LITERAL(0, 10),  // "MainWindow"
        QT_MOC_LITERAL(11, 12),  // "on_connected"
        QT_MOC_LITERAL(24, 0),  // ""
        QT_MOC_LITERAL(25, 15),  // "on_disconnected"
        QT_MOC_LITERAL(41, 19),  // "on_connection_error"
        QT_MOC_LITERAL(61, 5),  // "error"
        QT_MOC_LITERAL(67, 16),  // "on_login_success"
        QT_MOC_LITERAL(84, 8),  // "uint32_t"
        QT_MOC_LITERAL(93, 7),  // "user_id"
        QT_MOC_LITERAL(101, 8),  // "username"
        QT_MOC_LITERAL(110, 15),  // "on_login_failed"
        QT_MOC_LITERAL(126, 19),  // "on_message_received"
        QT_MOC_LITERAL(146, 12),  // "from_user_id"
        QT_MOC_LITERAL(159, 13),  // "from_username"
        QT_MOC_LITERAL(173, 4),  // "text"
        QT_MOC_LITERAL(178, 25),  // "on_group_message_received"
        QT_MOC_LITERAL(204, 8),  // "group_id"
        QT_MOC_LITERAL(213, 16),  // "on_group_created"
        QT_MOC_LITERAL(230, 10),  // "group_name"
        QT_MOC_LITERAL(241, 15),  // "on_group_joined"
        QT_MOC_LITERAL(257, 23),  // "on_groups_list_received"
        QT_MOC_LITERAL(281, 9),  // "json_list"
        QT_MOC_LITERAL(291, 9),  // "on_notify"
        QT_MOC_LITERAL(301, 7),  // "message"
        QT_MOC_LITERAL(309, 16),  // "on_login_clicked"
        QT_MOC_LITERAL(326, 19),  // "on_register_clicked"
        QT_MOC_LITERAL(346, 29),  // "on_switch_to_register_clicked"
        QT_MOC_LITERAL(376, 26),  // "on_switch_to_login_clicked"
        QT_MOC_LITERAL(403, 15),  // "on_send_clicked"
        QT_MOC_LITERAL(419, 23),  // "on_create_group_clicked"
        QT_MOC_LITERAL(443, 21),  // "on_join_group_clicked"
        QT_MOC_LITERAL(465, 16),  // "on_user_selected"
        QT_MOC_LITERAL(482, 11),  // "QModelIndex"
        QT_MOC_LITERAL(494, 5),  // "index"
        QT_MOC_LITERAL(500, 17),  // "on_group_selected"
        QT_MOC_LITERAL(518, 23),  // "on_message_text_changed"
        QT_MOC_LITERAL(542, 20)   // "on_heartbeat_timeout"
    },
    "MainWindow",
    "on_connected",
    "",
    "on_disconnected",
    "on_connection_error",
    "error",
    "on_login_success",
    "uint32_t",
    "user_id",
    "username",
    "on_login_failed",
    "on_message_received",
    "from_user_id",
    "from_username",
    "text",
    "on_group_message_received",
    "group_id",
    "on_group_created",
    "group_name",
    "on_group_joined",
    "on_groups_list_received",
    "json_list",
    "on_notify",
    "message",
    "on_login_clicked",
    "on_register_clicked",
    "on_switch_to_register_clicked",
    "on_switch_to_login_clicked",
    "on_send_clicked",
    "on_create_group_clicked",
    "on_join_group_clicked",
    "on_user_selected",
    "QModelIndex",
    "index",
    "on_group_selected",
    "on_message_text_changed",
    "on_heartbeat_timeout"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSMainWindowENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
      22,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  146,    2, 0x08,    1 /* Private */,
       3,    0,  147,    2, 0x08,    2 /* Private */,
       4,    1,  148,    2, 0x08,    3 /* Private */,
       6,    2,  151,    2, 0x08,    5 /* Private */,
      10,    1,  156,    2, 0x08,    8 /* Private */,
      11,    3,  159,    2, 0x08,   10 /* Private */,
      15,    4,  166,    2, 0x08,   14 /* Private */,
      17,    2,  175,    2, 0x08,   19 /* Private */,
      19,    1,  180,    2, 0x08,   22 /* Private */,
      20,    1,  183,    2, 0x08,   24 /* Private */,
      22,    1,  186,    2, 0x08,   26 /* Private */,
      24,    0,  189,    2, 0x08,   28 /* Private */,
      25,    0,  190,    2, 0x08,   29 /* Private */,
      26,    0,  191,    2, 0x08,   30 /* Private */,
      27,    0,  192,    2, 0x08,   31 /* Private */,
      28,    0,  193,    2, 0x08,   32 /* Private */,
      29,    0,  194,    2, 0x08,   33 /* Private */,
      30,    0,  195,    2, 0x08,   34 /* Private */,
      31,    1,  196,    2, 0x08,   35 /* Private */,
      34,    1,  199,    2, 0x08,   37 /* Private */,
      35,    0,  202,    2, 0x08,   39 /* Private */,
      36,    0,  203,    2, 0x08,   40 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, 0x80000000 | 7, QMetaType::QString,    8,    9,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, 0x80000000 | 7, QMetaType::QString, QMetaType::QString,   12,   13,   14,
    QMetaType::Void, 0x80000000 | 7, 0x80000000 | 7, QMetaType::QString, QMetaType::QString,   16,   12,   13,   14,
    QMetaType::Void, 0x80000000 | 7, QMetaType::QString,   16,   18,
    QMetaType::Void, 0x80000000 | 7,   16,
    QMetaType::Void, QMetaType::QString,   21,
    QMetaType::Void, QMetaType::QString,   23,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 32,   33,
    QMetaType::Void, 0x80000000 | 32,   33,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSMainWindowENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSMainWindowENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSMainWindowENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>,
        // method 'on_connected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_disconnected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_connection_error'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'on_login_success'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<uint32_t, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'on_login_failed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'on_message_received'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<uint32_t, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'on_group_message_received'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<uint32_t, std::false_type>,
        QtPrivate::TypeAndForceComplete<uint32_t, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'on_group_created'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<uint32_t, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'on_group_joined'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<uint32_t, std::false_type>,
        // method 'on_groups_list_received'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'on_notify'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'on_login_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_register_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_switch_to_register_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_switch_to_login_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_send_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_create_group_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_join_group_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_user_selected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QModelIndex &, std::false_type>,
        // method 'on_group_selected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QModelIndex &, std::false_type>,
        // method 'on_message_text_changed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_heartbeat_timeout'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_connected(); break;
        case 1: _t->on_disconnected(); break;
        case 2: _t->on_connection_error((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->on_login_success((*reinterpret_cast< std::add_pointer_t<uint32_t>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 4: _t->on_login_failed((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 5: _t->on_message_received((*reinterpret_cast< std::add_pointer_t<uint32_t>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3]))); break;
        case 6: _t->on_group_message_received((*reinterpret_cast< std::add_pointer_t<uint32_t>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<uint32_t>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[4]))); break;
        case 7: _t->on_group_created((*reinterpret_cast< std::add_pointer_t<uint32_t>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 8: _t->on_group_joined((*reinterpret_cast< std::add_pointer_t<uint32_t>>(_a[1]))); break;
        case 9: _t->on_groups_list_received((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 10: _t->on_notify((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 11: _t->on_login_clicked(); break;
        case 12: _t->on_register_clicked(); break;
        case 13: _t->on_switch_to_register_clicked(); break;
        case 14: _t->on_switch_to_login_clicked(); break;
        case 15: _t->on_send_clicked(); break;
        case 16: _t->on_create_group_clicked(); break;
        case 17: _t->on_join_group_clicked(); break;
        case 18: _t->on_user_selected((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1]))); break;
        case 19: _t->on_group_selected((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1]))); break;
        case 20: _t->on_message_text_changed(); break;
        case 21: _t->on_heartbeat_timeout(); break;
        default: ;
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSMainWindowENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 22)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 22;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 22)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 22;
    }
    return _id;
}
QT_WARNING_POP
