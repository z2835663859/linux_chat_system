#include "main_window.hpp"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSplitter>
#include <QSpinBox>
#include <QStackedWidget>
#include <QTimer>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMessageBox>
#include <QApplication>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QInputDialog>
#include <QDateTime>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDir>


void MainWindow::init_database() {
    QString db_path = QDir::currentPath() + "/client_data.db";
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(db_path);
    if (!db.open()) {
        QMessageBox::critical(this, "数据库错误", "无法连接本地数据库: " + db.lastError().text());
        return;
    }
    
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS users ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "username TEXT UNIQUE, "
               "password TEXT)");
}

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      current_user_id_(0),
      current_group_id_(0),
      is_group_chat_(false) {
    
    // Initialize models
    current_chat_model_ = std::make_unique<ChatModel>();
    group_model_ = std::make_unique<GroupModel>();
    user_model_ = std::make_unique<UserModel>();
    
    // Initialize network
    network_ = std::make_unique<IMClientNetwork>();
    
    // Setup UI
    setWindowTitle("IM Client - Modern GUI");
    setWindowIcon(QIcon());
    setGeometry(100, 100, 1200, 700);
    
    setup_ui();
    setup_styles();
    connect_signals();
    init_database();
    
    // Setup heartbeat timer
    heartbeat_timer_ = new QTimer(this);
    connect(heartbeat_timer_, &QTimer::timeout, this, &MainWindow::on_heartbeat_timeout);
    
    show_login_page();
}

MainWindow::~MainWindow() {
    network_->disconnect_from_server();
}

void MainWindow::setup_ui() {
    QStackedWidget* stacked = new QStackedWidget(this);
    setCentralWidget(stacked);
    
    // ============= Login Page =============
    login_widget_ = new QWidget();
    login_widget_->setStyleSheet("background: transparent;");
    QVBoxLayout* login_main_layout = new QVBoxLayout(login_widget_);
    login_main_layout->setAlignment(Qt::AlignCenter);
    
    QWidget* login_card = new QWidget();
    login_card->setObjectName("CardWidget");
    login_card->setFixedSize(420, 520);
    QVBoxLayout* login_layout = new QVBoxLayout(login_card);
    login_layout->setSpacing(20);
    login_layout->setContentsMargins(40, 40, 40, 40);
    
    QLabel* title = new QLabel("欢迎登录");
    title->setStyleSheet("font-size: 28px; font-weight: 600; color: #1a1a1a;");
    title->setAlignment(Qt::AlignCenter);
    login_layout->addWidget(title);
    
    QGroupBox* form_group = new QGroupBox();
    QFormLayout* form_layout = new QFormLayout(form_group);
    form_layout->setSpacing(15);
    
    server_host_input_ = new QLineEdit("127.0.0.1");
    server_port_input_ = new QSpinBox();
    server_port_input_->setMinimum(1);
    server_port_input_->setMaximum(65535);
    server_port_input_->setValue(9999);
    
    username_input_ = new QLineEdit();
    username_input_->setPlaceholderText("请输入用户名");
    
    password_input_ = new QLineEdit();
    password_input_->setPlaceholderText("请输入密码");
    password_input_->setEchoMode(QLineEdit::Password);
    
    form_layout->addRow("服务器 IP:", server_host_input_);
    form_layout->addRow("端口:", server_port_input_);
    form_layout->addRow("用户名:", username_input_);
    form_layout->addRow("密码:", password_input_);
    
    login_layout->addWidget(form_group);
    
    login_button_ = new QPushButton("登 录");
    login_button_->setMinimumHeight(40);
    login_button_->setObjectName("PrimaryButton");
    login_layout->addWidget(login_button_);
    
    // Register Button
    QPushButton* switch_register_btn = new QPushButton("没有账号？点击注册");
    switch_register_btn->setStyleSheet("background: transparent; color: #005fb8; border: none; text-decoration: underline;");
    switch_register_btn->setCursor(Qt::PointingHandCursor);
    login_layout->addWidget(switch_register_btn);
    
    login_status_label_ = new QLabel();
    login_status_label_->setAlignment(Qt::AlignCenter);
    login_status_label_->setStyleSheet("color: #d32f2f; font-weight: 500;");
    login_layout->addWidget(login_status_label_);
    login_layout->addStretch();
    
    login_main_layout->addWidget(login_card);

    // ============= Register Page =============
    register_widget_ = new QWidget();
    register_widget_->setStyleSheet("background: transparent;");
    QVBoxLayout* register_main_layout = new QVBoxLayout(register_widget_);
    register_main_layout->setAlignment(Qt::AlignCenter);

    QWidget* register_card = new QWidget();
    register_card->setObjectName("CardWidget");
    register_card->setFixedSize(420, 520);
    QVBoxLayout* register_layout = new QVBoxLayout(register_card);
    register_layout->setSpacing(20);
    register_layout->setContentsMargins(40, 40, 40, 40);

    QLabel* reg_title = new QLabel("账号注册");
    reg_title->setStyleSheet("font-size: 28px; font-weight: 600; color: #1a1a1a;");
    reg_title->setAlignment(Qt::AlignCenter);
    register_layout->addWidget(reg_title);

    QGroupBox* reg_form_group = new QGroupBox();
    QFormLayout* reg_form_layout = new QFormLayout(reg_form_group);
    reg_form_layout->setSpacing(15);

    reg_username_input_ = new QLineEdit();
    reg_username_input_->setPlaceholderText("请输入用户名");

    reg_password_input_ = new QLineEdit();
    reg_password_input_->setPlaceholderText("请输入密码");
    reg_password_input_->setEchoMode(QLineEdit::Password);

    reg_password_confirm_input_ = new QLineEdit();
    reg_password_confirm_input_->setPlaceholderText("请确认密码");
    reg_password_confirm_input_->setEchoMode(QLineEdit::Password);

    reg_form_layout->addRow("用户名:", reg_username_input_);
    reg_form_layout->addRow("密码:", reg_password_input_);
    reg_form_layout->addRow("确认密码:", reg_password_confirm_input_);

    register_layout->addWidget(reg_form_group);

    reg_button_ = new QPushButton("注 册");
    reg_button_->setMinimumHeight(40);
    reg_button_->setObjectName("PrimaryButton");
    register_layout->addWidget(reg_button_);

    QPushButton* switch_login_btn = new QPushButton("已有账号？直接登录");
    switch_login_btn->setStyleSheet("background: transparent; color: #005fb8; border: none; text-decoration: underline;");
    switch_login_btn->setCursor(Qt::PointingHandCursor);
    register_layout->addWidget(switch_login_btn);

    register_layout->addStretch();
    register_main_layout->addWidget(register_card);

    connect(switch_register_btn, &QPushButton::clicked, this, &MainWindow::on_switch_to_register_clicked);
    connect(switch_login_btn, &QPushButton::clicked, this, &MainWindow::on_switch_to_login_clicked);
    connect(reg_button_, &QPushButton::clicked, this, &MainWindow::on_register_clicked);
    
    // ============= Main Page =============
    main_widget_ = new QWidget();
    QHBoxLayout* main_layout = new QHBoxLayout(main_widget_);
    main_layout->setContentsMargins(0, 0, 0, 0);
    main_layout->setSpacing(0);
    
    // Left sidebar (Fluent Nav)
    QWidget* sidebar_widget = new QWidget();
    sidebar_widget->setObjectName("Sidebar");
    sidebar_widget->setMinimumWidth(260);
    sidebar_widget->setMaximumWidth(260);
    QVBoxLayout* sidebar_layout = new QVBoxLayout(sidebar_widget);
    sidebar_layout->setContentsMargins(10, 20, 10, 20);
    sidebar_layout->setSpacing(5);
    
    QLabel* search_label = new QLabel("💬 现代通讯 UI"); 
    search_label->setStyleSheet("font-size: 16px; font-weight: bold; margin-left: 10px; margin-bottom: 10px; color: #1a1a1a;");
    sidebar_layout->addWidget(search_label);
    
    QLabel* users_label = new QLabel("联系人");
    users_label->setStyleSheet("font-weight: 600; font-size: 13px; color: #555; margin-left: 10px; margin-top: 10px;");
    sidebar_layout->addWidget(users_label);
    
    user_list_view_ = new QListView();
    user_list_view_->setModel(user_model_.get());
    user_list_view_->setObjectName("FluentList");
    sidebar_layout->addWidget(user_list_view_);
    
    QLabel* groups_label = new QLabel("群组");
    groups_label->setStyleSheet("font-weight: 600; font-size: 13px; color: #555; margin-left: 10px; margin-top: 10px;");
    sidebar_layout->addWidget(groups_label);
    
    group_list_view_ = new QListView();
    group_list_view_->setModel(group_model_.get());
    group_list_view_->setObjectName("FluentList");
    sidebar_layout->addWidget(group_list_view_);
    
    create_group_button_ = new QPushButton("创建群组");
    join_group_button_ = new QPushButton("加入群组");
    sidebar_layout->addWidget(create_group_button_);
    sidebar_layout->addWidget(join_group_button_);
    
    // Right Content Area
    QWidget* content_widget = new QWidget();
    content_widget->setObjectName("MainContent");
    QVBoxLayout* content_layout = new QVBoxLayout(content_widget);
    content_layout->setContentsMargins(30, 20, 30, 30);
    content_layout->setSpacing(20);
    
    // Toolbar inside right content
    QHBoxLayout* toolbar_layout = new QHBoxLayout();
    user_info_label_ = new QLabel("用户: 未登录");
    user_info_label_->setStyleSheet("font-size: 14px; font-weight: 500; color: #444;");
    status_label_ = new QLabel("❌ 未连接");
    status_label_->setStyleSheet("color: #d32f2f; font-weight: bold;");
    toolbar_layout->addWidget(user_info_label_);
    toolbar_layout->addStretch();
    toolbar_layout->addWidget(status_label_);
    content_layout->addLayout(toolbar_layout);
    
    // Banner
    QWidget* banner_widget = new QWidget();
    banner_widget->setObjectName("BannerWidget");
    banner_widget->setMinimumHeight(140);
    banner_widget->setMaximumHeight(160);
    QVBoxLayout* banner_layout = new QVBoxLayout(banner_widget);
    banner_layout->setContentsMargins(25, 25, 25, 25);
    QLabel* banner_title = new QLabel("现代聊天体验");
    banner_title->setStyleSheet("font-size: 30px; font-weight: 800; color: #1a1a1a; background: transparent;");
    QLabel* banner_subtitle = new QLabel("尽享现代化的通讯界面与便捷操作。\n请在左侧选择一个联系人或群组开始聊天。");
    banner_subtitle->setStyleSheet("font-size: 14px; color: #444; background: transparent;");
    banner_layout->addWidget(banner_title);
    banner_layout->addWidget(banner_subtitle);
    banner_layout->addStretch();
    content_layout->addWidget(banner_widget);
    
    // Chat card
    QWidget* chat_card = new QWidget();
    chat_card->setObjectName("CardWidget");
    QVBoxLayout* chat_layout = new QVBoxLayout(chat_card);
    chat_layout->setContentsMargins(0, 0, 0, 0);
    chat_layout->setSpacing(0);
    
    QWidget* chat_header = new QWidget();
    chat_header->setObjectName("ChatHeader");
    chat_header->setMinimumHeight(60);
    QHBoxLayout* header_layout = new QHBoxLayout(chat_header);
    current_chat_label_ = new QLabel("请选择一个联系人或群组");
    current_chat_label_->setStyleSheet("font-weight: bold; font-size: 16px; color: #1a1a1a;");
    header_layout->addWidget(current_chat_label_);
    chat_layout->addWidget(chat_header);
    
    chat_history_view_ = new QListView();
    chat_history_view_->setModel(current_chat_model_.get());
    chat_history_view_->setObjectName("ChatList");
    chat_layout->addWidget(chat_history_view_);
    
    QWidget* input_container = new QWidget();
    input_container->setObjectName("InputContainer");
    QHBoxLayout* input_layout = new QHBoxLayout(input_container);
    input_layout->setContentsMargins(15, 15, 15, 15);
    input_layout->setSpacing(15);
    
    message_input_ = new QTextEdit();
    message_input_->setMaximumHeight(45);
    message_input_->setPlaceholderText("请输入消息...");
    message_input_->setObjectName("MessageInput");
    
    send_button_ = new QPushButton("发送");
    send_button_->setFixedSize(80, 45);
    send_button_->setObjectName("PrimaryButton");
    
    input_layout->addWidget(message_input_);
    input_layout->addWidget(send_button_);
    
    chat_layout->addWidget(input_container);
    content_layout->addWidget(chat_card, 1);
    
    main_layout->addWidget(sidebar_widget);
    main_layout->addWidget(content_widget, 1);
    
    // Add to stacked widget
    stacked->addWidget(login_widget_);
    stacked->addWidget(register_widget_);
    stacked->addWidget(main_widget_);
}

void MainWindow::setup_styles() {
    QString fluent_style = R"(
        QMainWindow {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #e3f2fd, stop:1 #f3e5f5);
        }
        QWidget {
            font-family: 'Segoe UI', -apple-system, BlinkMacSystemFont, Roboto, Arial, sans-serif;
        }
        #Sidebar {
            background: transparent;
            border-right: 1px solid rgba(0, 0, 0, 0.05);
        }
        #MainContent {
            background: transparent;
        }
        #BannerWidget {
            background-color: rgba(255, 255, 255, 0.4);
            border-radius: 12px;
            border: 1px solid rgba(255, 255, 255, 0.6);
        }
        #CardWidget {
            background-color: rgba(255, 255, 255, 0.85);
            border-radius: 12px;
            border: 1px solid rgba(0, 0, 0, 0.05);
        }
        #ChatHeader {
            background-color: transparent;
            border-bottom: 1px solid #f0f0f0;
            border-top-left-radius: 12px;
            border-top-right-radius: 12px;
            padding: 0 20px;
        }
        #InputContainer {
            background-color: #ffffff;
            border-bottom-left-radius: 12px;
            border-bottom-right-radius: 12px;
            border-top: 1px solid #f0f0f0;
        }
        #FluentList {
            background-color: transparent;
            border: none;
            outline: none;
        }
        #FluentList::item {
            padding: 10px 15px;
            margin: 2px 8px;
            border-radius: 6px;
            color: #1a1a1a;
            font-size: 14px;
        }
        #FluentList::item:hover {
            background-color: rgba(0, 0, 0, 0.05);
        }
        #FluentList::item:selected {
            background-color: rgba(255, 255, 255, 0.6);
            color: #005fb8;
            font-weight: bold;
        }
        #ChatList {
            background-color: transparent;
            border: none;
            outline: none;
        }
        #ChatList::item {
            padding: 10px 20px;
            border: none;
        }
        QLineEdit, QSpinBox {
            background-color: #ffffff;
            color: #1a1a1a;
            border: 1px solid #d1d1d1;
            border-bottom: 2px solid #8e8e8e;
            border-radius: 4px;
            padding: 8px 12px;
            font-size: 14px;
            selection-background-color: #0078d4;
        }
        QLineEdit:focus, QSpinBox:focus {
            border-bottom: 2px solid #0078d4;
            background-color: #ffffff;
        }
        #MessageInput {
            background-color: #ffffff;
            color: #1a1a1a;
            border: 1px solid #e0e0e0;
            border-radius: 6px;
            padding: 10px;
            font-size: 14px;
        }
        #MessageInput:focus {
            border: 1px solid #0078d4;
        }
        QPushButton {
            background-color: #fdfdfd;
            color: #1a1a1a;
            border: 1px solid #d1d1d1;
            border-radius: 6px;
            padding: 8px 16px;
            font-size: 14px;
        }
        QPushButton:hover {
            background-color: #f5f5f5;
        }
        QPushButton:pressed {
            background-color: #ededed;
            color: #666666;
        }
        #PrimaryButton {
            background-color: #005fb8;
            color: white;
            border: none;
            font-weight: 600;
            border-radius: 6px;
        }
        #PrimaryButton:hover {
            background-color: #0056a6;
        }
        #PrimaryButton:pressed {
            background-color: #004c93;
        }
        QLabel {
            color: #1a1a1a;
        }
        QGroupBox {
            color: #1a1a1a;
            border: none;
            margin-top: 10px;
        }
        QGroupBox::title {
            subcontrol-origin: margin;
            left: 0px;
            padding: 0;
            font-weight: 600;
        }
        QScrollBar:vertical {
            border: none;
            background: transparent;
            width: 8px;
            margin: 0px;
        }
        QScrollBar::handle:vertical {
            background: #cdcdcd;
            min-height: 30px;
            border-radius: 4px;
        }
        QScrollBar::handle:vertical:hover {
            background: #a6a6a6;
        }
        QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
            height: 0px;
        }
        QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {
            background: none;
        }
    )";
    
    qApp->setStyle("Fusion");
    qApp->setStyleSheet(fluent_style);
}

void MainWindow::connect_signals() {
    // Network signals
    connect(network_.get(), &IMClientNetwork::connected, this, &MainWindow::on_connected);
    connect(network_.get(), &IMClientNetwork::disconnected, this, &MainWindow::on_disconnected);
    connect(network_.get(), &IMClientNetwork::connection_error, this, &MainWindow::on_connection_error);
    connect(network_.get(), &IMClientNetwork::login_success, this, &MainWindow::on_login_success);
    connect(network_.get(), &IMClientNetwork::login_failed, this, &MainWindow::on_login_failed);
    connect(network_.get(), &IMClientNetwork::register_success, this, [this]() {
        QMessageBox::information(this, "注册成功", "注册成功，请登录！");
        show_login_page();
    });
    connect(network_.get(), &IMClientNetwork::register_failed, this, [this](const QString& error) {
        QMessageBox::warning(this, "注册失败", "注册失败: " + error);
    });
    connect(network_.get(), &IMClientNetwork::message_received, this, &MainWindow::on_message_received);
    connect(network_.get(), &IMClientNetwork::group_message_received, this, &MainWindow::on_group_message_received);
    connect(network_.get(), &IMClientNetwork::group_created, this, &MainWindow::on_group_created);
    connect(network_.get(), &IMClientNetwork::group_joined, this, &MainWindow::on_group_joined);
    connect(network_.get(), &IMClientNetwork::groups_list_received, this, &MainWindow::on_groups_list_received);
    connect(network_.get(), &IMClientNetwork::notify, this, &MainWindow::on_notify);
    
    // UI signals
    connect(login_button_, &QPushButton::clicked, this, &MainWindow::on_login_clicked);
    connect(send_button_, &QPushButton::clicked, this, &MainWindow::on_send_clicked);
    connect(create_group_button_, &QPushButton::clicked, this, &MainWindow::on_create_group_clicked);
    connect(join_group_button_, &QPushButton::clicked, this, &MainWindow::on_join_group_clicked);
    connect(user_list_view_, &QListView::clicked, this, &MainWindow::on_user_selected);
    connect(group_list_view_, &QListView::clicked, this, &MainWindow::on_group_selected);
    connect(message_input_, &QTextEdit::textChanged, this, &MainWindow::on_message_text_changed);
}

void MainWindow::show_login_page() {
    ((QStackedWidget*)centralWidget())->setCurrentWidget(login_widget_);
}

void MainWindow::show_register_page() {
    ((QStackedWidget*)centralWidget())->setCurrentWidget(register_widget_);
}

void MainWindow::on_switch_to_register_clicked() {
    show_register_page();
}

void MainWindow::on_switch_to_login_clicked() {
    show_login_page();
}

void MainWindow::show_main_page() {
    ((QStackedWidget*)centralWidget())->setCurrentWidget(main_widget_);
}

void MainWindow::on_login_clicked() {
    QString host = server_host_input_->text();
    int port = server_port_input_->value();
    QString username = username_input_->text();
    QString password = password_input_->text();
    
    if (username.isEmpty() || password.isEmpty()) {
        login_status_label_->setText("❌ Please enter username and password");
        return;
    }
    
    if (host.isEmpty()) {
        host = "localhost";
        server_host_input_->setText(host);
    }
    
    login_status_label_->setText("Connecting to " + host + ":" + QString::number(port) + "...");
    
    // Save login credentials for when connection succeeds
    pending_login_username_ = username;
    pending_login_password_ = password;
    
    is_registering_ = false;
    network_->connect_to_server(host, port);
}

void MainWindow::on_register_clicked() {
    QString host = server_host_input_->text();
    int port = server_port_input_->value();
    QString username = reg_username_input_->text();
    QString password = reg_password_input_->text();
    QString confirm_pwd = reg_password_confirm_input_->text();
    
    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "错误", "用户名和密码不能为空！");
        return;
    }
    if (password != confirm_pwd) {
        QMessageBox::warning(this, "错误", "两次输入的密码不一致！");
        return;
    }
    if (host.isEmpty()) {
        host = "localhost";
    }
    
    pending_login_username_ = username;
    pending_login_password_ = password;
    is_registering_ = true;
    
    network_->connect_to_server(host, port);
}

void MainWindow::on_connected() {
    login_status_label_->setText("已连接...");
    
    if (!pending_login_username_.isEmpty()) {
        if (is_registering_) {
            network_->send_register(pending_login_username_, pending_login_password_);
        } else {
            network_->send_login(pending_login_username_, pending_login_password_);
        }
        pending_login_username_.clear();
        pending_login_password_.clear();
        is_registering_ = false;
    }
}

void MainWindow::on_disconnected() {
    status_label_->setText("❌ 已断开连接");
    status_label_->setStyleSheet("color: #d32f2f;");
    heartbeat_timer_->stop();
    show_login_page();
}

void MainWindow::on_connection_error(const QString& error) {
    login_status_label_->setText("❌ Connection error: " + error);
}

void MainWindow::on_login_success(uint32_t user_id, const QString& username) {
    user_info_label_->setText(QString("用户: %1").arg(username));
    status_label_->setText("✅ 已连接");
    status_label_->setStyleSheet("color: #4caf50;");
    
    show_main_page();
    
    // Add default test contacts (bob and charlie)
    if (username != "bob") {
        UserInfo user;
        user.user_id = 2;
        user.username = "bob";
        user_model_->add_user(user);
    }
    if (username != "charlie") {
        UserInfo user;
        user.user_id = 3;
        user.username = "charlie";
        user_model_->add_user(user);
    }
    if (username != "alice") {
        UserInfo user;
        user.user_id = 1;
        user.username = "alice";
        user_model_->add_user(user);
    }
    
    // Start heartbeat
    heartbeat_timer_->start(30000);  // 30 seconds
    
    // Load groups
    refresh_groups();
}

void MainWindow::on_login_failed(const QString& error) {
    login_status_label_->setText("❌ 登录失败: " + error);
}

void MainWindow::on_send_clicked() {
    QString text = message_input_->toPlainText().trimmed();
    if (text.isEmpty())
        return;
    
    if (is_group_chat_ && current_group_id_ > 0) {
        network_->send_chat_group(current_group_id_, text);
    } else if (!is_group_chat_ && current_user_id_ > 0) {
        network_->send_chat_to(current_user_id_, text);
    } else {
        return;  // No valid recipient selected
    }
    
    // Add to chat history
    ChatMessage msg;
    msg.from_user_id = network_->get_user_id();
    msg.from_username = network_->get_username();
    msg.text = text;
    msg.timestamp = QDateTime::currentDateTime();
    msg.is_sender = true;
    msg.group_id = is_group_chat_ ? current_group_id_ : 0;
    
    // Add directly to the current model that is displayed
    current_chat_model_->add_message(msg);
    
    // Also save to backup for later access
    if (is_group_chat_) {
        uint32_t key = current_group_id_ + 1000000;
        if (chat_histories_.find(key) == chat_histories_.end()) {
            chat_histories_[key] = std::make_unique<ChatModel>();
        }
        if (chat_histories_[key]) {
            chat_histories_[key]->add_message(msg);
        }
    } else {
        if (chat_histories_.find(current_user_id_) == chat_histories_.end()) {
            chat_histories_[current_user_id_] = std::make_unique<ChatModel>();
        }
        if (chat_histories_[current_user_id_]) {
            chat_histories_[current_user_id_]->add_message(msg);
        }
    }
    
    message_input_->clear();
    chat_history_view_->scrollToBottom();
}

void MainWindow::on_message_received(uint32_t from_user_id, const QString& from_username, const QString& text) {
    ChatMessage msg;
    msg.from_user_id = from_user_id;
    msg.from_username = from_username;
    msg.text = text;
    msg.timestamp = QDateTime::currentDateTime();
    msg.is_sender = false;
    msg.group_id = 0;
    
    // Store in history
    if (chat_histories_.find(from_user_id) == chat_histories_.end()) {
        chat_histories_[from_user_id] = std::make_unique<ChatModel>();
    }
    chat_histories_[from_user_id]->add_message(msg);
    
    // If this is current chat, show immediately
    if (!is_group_chat_ && current_user_id_ == from_user_id) {
        current_chat_model_->add_message(msg);
        chat_history_view_->scrollToBottom();
    }
}

void MainWindow::on_group_message_received(uint32_t group_id, uint32_t from_user_id,
                                           const QString& from_username, const QString& text) {
    ChatMessage msg;
    msg.from_user_id = from_user_id;
    msg.from_username = from_username;
    msg.text = text;
    msg.timestamp = QDateTime::currentDateTime();
    msg.is_sender = false;
    msg.group_id = group_id;
    
    uint32_t key = group_id + 1000000;
    if (chat_histories_.find(key) == chat_histories_.end()) {
        chat_histories_[key] = std::make_unique<ChatModel>();
    }
    chat_histories_[key]->add_message(msg);
    
    if (is_group_chat_ && current_group_id_ == group_id) {
        current_chat_model_->add_message(msg);
        chat_history_view_->scrollToBottom();
    }
}

void MainWindow::on_group_created(uint32_t group_id, const QString& group_name) {
    GroupInfo group;
    group.group_id = group_id;
    group.group_name = group_name;
    group.member_count = 1;
    
    group_model_->add_group(group);
    chat_histories_[group_id + 1000000] = std::make_unique<ChatModel>();
    
    // 只更新创建者本人的群组列表，不广播给所有人
    // 其他用户需要主动加入群组
    
    // 显示群组ID给用户
    QMessageBox::information(this, "群组创建成功", 
        QString("群组 '%1' 创建成功！\n\n群组ID: %2\n\n请将此ID告诉其他用户来加入群组")
        .arg(group_name)
        .arg(group_id));
}

void MainWindow::on_group_joined(uint32_t group_id) {
    // 加入群组成功后，刷新群组列表
    refresh_groups();
}

void MainWindow::on_create_group_clicked() {
    
    // Create a simple custom dialog without any macOS native components
    QDialog dialog(this);
    dialog.setWindowTitle("创建群组");
    dialog.setMinimumWidth(300);
    
    QVBoxLayout* layout = new QVBoxLayout(&dialog);
    layout->setSpacing(12);
    layout->setContentsMargins(16, 16, 16, 16);
    
    // Label
    QLabel* label = new QLabel("群组名称:");
    label->setStyleSheet("color: #ffffff; font-weight: bold;");
    layout->addWidget(label);
    
    // Input field
    QLineEdit* input_field = new QLineEdit();
    input_field->setStyleSheet(
        "QLineEdit {"
        "    background-color: #3d3d3d;"
        "    color: #ffffff;"
        "    border: 1px solid #555;"
        "    border-radius: 4px;"
        "    padding: 6px;"
        "    font-size: 13px;"
        "}"
    );
    input_field->setFocus();
    layout->addWidget(input_field);
    
    // Buttons
    QHBoxLayout* button_layout = new QHBoxLayout();
    button_layout->addStretch();
    
    QPushButton* create_btn = new QPushButton("创建");
    create_btn->setStyleSheet(
        "QPushButton {"
        "    background-color: #0078d4;"
        "    color: white;"
        "    border: none;"
        "    padding: 6px 20px;"
        "    border-radius: 4px;"
        "    font-weight: bold;"
        "}"
        "QPushButton:hover { background-color: #1084d7; }"
    );
    create_btn->setMinimumWidth(80);
    button_layout->addWidget(create_btn);
    
    QPushButton* cancel_btn = new QPushButton("取消");
    cancel_btn->setStyleSheet(
        "QPushButton {"
        "    background-color: #555555;"
        "    color: white;"
        "    border: none;"
        "    padding: 6px 20px;"
        "    border-radius: 4px;"
        "}"
        "QPushButton:hover { background-color: #666666; }"
    );
    cancel_btn->setMinimumWidth(80);
    button_layout->addWidget(cancel_btn);
    
    layout->addLayout(button_layout);
    
    // Dialog styling
    dialog.setStyleSheet(
        "QDialog {"
        "    background-color: #2d2d2d;"
        "}"
    );
    
    // Connect buttons
    connect(create_btn, &QPushButton::clicked, &dialog, &QDialog::accept);
    connect(cancel_btn, &QPushButton::clicked, &dialog, &QDialog::reject);
    
    // Run dialog
    int result = dialog.exec();
    
    if (result == QDialog::Accepted) {
        QString group_name = input_field->text().trimmed();
        if (!group_name.isEmpty()) {
            network_->send_create_group(group_name, "");
        }
    }
}

void MainWindow::on_join_group_clicked() {
    // Create a simple custom dialog without any macOS native components
    QDialog dialog(this);
    dialog.setWindowTitle("加入群组");
    dialog.setMinimumWidth(300);
    
    QVBoxLayout* layout = new QVBoxLayout(&dialog);
    layout->setSpacing(12);
    layout->setContentsMargins(16, 16, 16, 16);
    
    // Label
    QLabel* label = new QLabel("群组ID:");
    label->setStyleSheet("color: #ffffff; font-weight: bold;");
    layout->addWidget(label);
    
    // Input field
    QLineEdit* input_field = new QLineEdit();
    input_field->setStyleSheet(
        "QLineEdit {"
        "    background-color: #3d3d3d;"
        "    color: #ffffff;"
        "    border: 1px solid #555;"
        "    border-radius: 4px;"
        "    padding: 6px;"
        "    font-size: 13px;"
        "}"
    );
    input_field->setFocus();
    layout->addWidget(input_field);
    
    // Buttons
    QHBoxLayout* button_layout = new QHBoxLayout();
    button_layout->addStretch();
    
    QPushButton* join_btn = new QPushButton("加入");
    join_btn->setStyleSheet(
        "QPushButton {"
        "    background-color: #0078d4;"
        "    color: white;"
        "    border: none;"
        "    padding: 6px 20px;"
        "    border-radius: 4px;"
        "    font-weight: bold;"
        "}"
        "QPushButton:hover { background-color: #1084d7; }"
    );
    join_btn->setMinimumWidth(80);
    button_layout->addWidget(join_btn);
    
    QPushButton* cancel_btn = new QPushButton("Cancel");
    cancel_btn->setStyleSheet(
        "QPushButton {"
        "    background-color: #555555;"
        "    color: white;"
        "    border: none;"
        "    padding: 6px 20px;"
        "    border-radius: 4px;"
        "}"
        "QPushButton:hover { background-color: #666666; }"
    );
    cancel_btn->setMinimumWidth(80);
    button_layout->addWidget(cancel_btn);
    
    layout->addLayout(button_layout);
    
    // Dialog styling
    dialog.setStyleSheet(
        "QDialog {"
        "    background-color: #2d2d2d;"
        "}"
    );
    
    // Connect buttons
    connect(join_btn, &QPushButton::clicked, &dialog, &QDialog::accept);
    connect(cancel_btn, &QPushButton::clicked, &dialog, &QDialog::reject);
    
    // Run dialog
    if (dialog.exec() == QDialog::Accepted) {
        QString group_id_str = input_field->text().trimmed();
        if (!group_id_str.isEmpty()) {
            uint32_t group_id = group_id_str.toUInt();
            network_->send_join_group(group_id);
        }
    }
}

void MainWindow::on_groups_list_received(const QString& json_list) {
    group_model_->clear_groups();  // 清除旧的群组列表
    
    QJsonDocument doc = QJsonDocument::fromJson(json_list.toUtf8());
    QJsonObject obj = doc.object();
    QJsonArray groups = obj["groups"].toArray();
    
    for (const auto& g : groups) {
        QJsonObject group_obj = g.toObject();
        GroupInfo group;
        group.group_id = group_obj["group_id"].toInt();
        group.group_name = group_obj["group_name"].toString();
        group.member_count = group_obj["member_count"].toInt();
        
        group_model_->add_group(group);
    }
}

void MainWindow::on_user_selected(const QModelIndex& index) {
    if (const UserInfo* user = user_model_->get_user(index.row())) {
        switch_to_user(user->user_id, user->username);
    }
}

void MainWindow::on_group_selected(const QModelIndex& index) {
    if (const GroupInfo* group = group_model_->get_group(index.row())) {
        switch_to_group(group->group_id, group->group_name);
    }
}

void MainWindow::on_message_text_changed() {
    // Auto-resize text edit
    send_button_->setEnabled(!message_input_->toPlainText().trimmed().isEmpty());
}

void MainWindow::on_notify(const QString& message) {
    QMessageBox::information(this, "通知", message);
}

void MainWindow::on_heartbeat_timeout() {
    network_->send_heartbeat();
}

void MainWindow::switch_to_user(uint32_t user_id, const QString& username) {
    is_group_chat_ = false;
    current_user_id_ = user_id;
    current_group_id_ = 0;
    current_chat_name_ = username;
    
    current_chat_label_->setText(QString("💬 与 %1 聊天").arg(username));
    
    // Load or create chat history
    if (chat_histories_.find(user_id) == chat_histories_.end()) {
        chat_histories_[user_id] = std::make_unique<ChatModel>();
    }
    
    current_chat_model_ = std::make_unique<ChatModel>();
    for (const auto& msg : chat_histories_[user_id]->messages()) {
        current_chat_model_->add_message(msg);
    }
    chat_history_view_->setModel(current_chat_model_.get());
}

void MainWindow::switch_to_group(uint32_t group_id, const QString& group_name) {
    is_group_chat_ = true;
    current_group_id_ = group_id;
    current_user_id_ = 0;
    current_chat_name_ = group_name;
    
    current_chat_label_->setText(QString("👥 群组: %1").arg(group_name));
    
    uint32_t key = group_id + 1000000;
    if (chat_histories_.find(key) == chat_histories_.end()) {
        chat_histories_[key] = std::make_unique<ChatModel>();
    }
    
    current_chat_model_ = std::make_unique<ChatModel>();
    for (const auto& msg : chat_histories_[key]->messages()) {
        current_chat_model_->add_message(msg);
    }
    chat_history_view_->setModel(current_chat_model_.get());
}

void MainWindow::refresh_groups() {
    network_->send_list_groups();
}

void MainWindow::closeEvent(QCloseEvent* event) {
    if (network_) {
        // 断开所有网络信号，防止在窗口销毁期间收到 server_im 兜底的“Logged out”等 notify 而弹窗阻塞
        network_->disconnect(this);
        network_->send_logout();
    }
    QMainWindow::closeEvent(event);
}
