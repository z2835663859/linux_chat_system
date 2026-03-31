import re

with open("qt_client/src/ui/main_window.cpp", "r") as f:
    content = f.read()

# Replace setup_ui
setup_ui_replacement = """void MainWindow::setup_ui() {
    QStackedWidget* stacked = new QStackedWidget(this);
    setCentralWidget(stacked);
    
    // ============= Login Page =============
    login_widget_ = new QWidget();
    login_widget_->setStyleSheet("background-color: #f3f3f3;");
    QVBoxLayout* login_main_layout = new QVBoxLayout(login_widget_);
    login_main_layout->setAlignment(Qt::AlignCenter);
    
    QWidget* login_card = new QWidget();
    login_card->setObjectName("CardWidget");
    login_card->setFixedSize(420, 480);
    QVBoxLayout* login_layout = new QVBoxLayout(login_card);
    login_layout->setSpacing(20);
    login_layout->setContentsMargins(40, 40, 40, 40);
    
    QLabel* title = new QLabel("Welcome to IM");
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
    username_input_->setPlaceholderText("Username");
    
    password_input_ = new QLineEdit();
    password_input_->setPlaceholderText("Password");
    password_input_->setEchoMode(QLineEdit::Password);
    
    form_layout->addRow("Server IP:", server_host_input_);
    form_layout->addRow("Port:", server_port_input_);
    form_layout->addRow("User:", username_input_);
    form_layout->addRow("Pwd:", password_input_);
    
    login_layout->addWidget(form_group);
    
    login_button_ = new QPushButton("Sign In");
    login_button_->setMinimumHeight(40);
    login_button_->setObjectName("PrimaryButton");
    login_layout->addWidget(login_button_);
    
    login_status_label_ = new QLabel();
    login_status_label_->setAlignment(Qt::AlignCenter);
    login_status_label_->setStyleSheet("color: #d32f2f; font-weight: 500;");
    login_layout->addWidget(login_status_label_);
    login_layout->addStretch();
    
    login_main_layout->addWidget(login_card);
    
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
    
    QLabel* search_label = new QLabel("Navigation"); 
    search_label->setStyleSheet("font-size: 16px; font-weight: bold; margin-left: 10px; margin-bottom: 10px; color: #1a1a1a;");
    sidebar_layout->addWidget(search_label);
    
    QLabel* users_label = new QLabel("Contacts");
    users_label->setStyleSheet("font-weight: 600; font-size: 13px; color: #555; margin-left: 10px; margin-top: 10px;");
    sidebar_layout->addWidget(users_label);
    
    user_list_view_ = new QListView();
    user_list_view_->setModel(user_model_.get());
    user_list_view_->setObjectName("FluentList");
    sidebar_layout->addWidget(user_list_view_);
    
    QLabel* groups_label = new QLabel("Groups");
    groups_label->setStyleSheet("font-weight: 600; font-size: 13px; color: #555; margin-left: 10px; margin-top: 10px;");
    sidebar_layout->addWidget(groups_label);
    
    group_list_view_ = new QListView();
    group_list_view_->setModel(group_model_.get());
    group_list_view_->setObjectName("FluentList");
    sidebar_layout->addWidget(group_list_view_);
    
    create_group_button_ = new QPushButton("Create Group");
    join_group_button_ = new QPushButton("Join Group");
    sidebar_layout->addWidget(create_group_button_);
    sidebar_layout->addWidget(join_group_button_);
    
    // Right Content Area
    QWidget* content_widget = new QWidget();
    content_widget->setObjectName("MainContent");
    QVBoxLayout* content_layout = new QVBoxLayout(content_widget);
    content_layout->setContentsMargins(30, 20, 30, 30);
    content_layout->setSpacing(20);
    
    // Toolbar inside right content (like Fluent breadcrumb + info)
    QHBoxLayout* toolbar_layout = new QHBoxLayout();
    user_info_label_ = new QLabel("User: Not logged in");
    user_info_label_ ->setStyleSheet("font-size: 14px; font-weight: 500; color: #444;");
    status_label_ = new QLabel("❌ Disconnected");
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
    QLabel* banner_title = new QLabel("FluentUI Chat Client");
    banner_title->setStyleSheet("font-size: 32px; font-weight: 800; color: #1a1a1a; background: transparent;");
    QLabel* banner_subtitle = new QLabel("A modern, fast, and elegantly designed messaging app.\\nSelect a contact on the left to start chatting.");
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
    
    QWidget* chat_header = new QWidget();
    chat_header->setObjectName("ChatHeader");
    chat_header->setMinimumHeight(60);
    QHBoxLayout* header_layout = new QHBoxLayout(chat_header);
    current_chat_label_ = new QLabel("Select a Contact or Group");
    current_chat_label_->setStyleSheet("font-weight: bold; font-size: 18px; color: #1a1a1a;");
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
    message_input_->setMaximumHeight(60);
    message_input_->setPlaceholderText("Type your message here...");
    message_input_->setObjectName("MessageInput");
    
    send_button_ = new QPushButton("Send");
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
    stacked->addWidget(main_widget_);
}"""

setup_styles_replacement = """void MainWindow::setup_styles() {
    QString fluent_style = R"(
        QMainWindow {
            background-color: #f3f3f3;
        }
        QWidget {
            font-family: "Segoe UI", -apple-system, BlinkMacSystemFont, Roboto, Arial, sans-serif;
        }
        #Sidebar {
            background-color: #f3f3f3;
            border-right: 1px solid #e5e5e5;
        }
        #MainContent {
            background-color: #fafafa;
        }
        #BannerWidget {
            background-color: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #e3f2fd, stop:1 #f3e5f5);
            border-radius: 12px;
            border: 1px solid #e0e0e0;
        }
        #CardWidget {
            background-color: #ffffff;
            border-radius: 12px;
            border: 1px solid #e0e0e0;
        }
        #ChatHeader {
            background-color: transparent;
            border-bottom: 1px solid #f0f0f0;
            border-top-left-radius: 12px;
            border-top-right-radius: 12px;
            padding: 0 20px;
        }
        #InputContainer {
            background-color: #fbfbfb;
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
            background-color: #e8e8e8;
        }
        #FluentList::item:selected {
            background-color: #e0eaf9;
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
            background-color: #0078d4;
            color: white;
            border: none;
            font-weight: 600;
            border-radius: 6px;
        }
        #PrimaryButton:hover {
            background-color: #106ebe;
        }
        #PrimaryButton:pressed {
            background-color: #005a9e;
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
}"""

content = re.sub(
    r'void MainWindow::setup_ui\(\)\s*\{.*?(?=\nvoid MainWindow::setup_styles\(\)|\nvoid MainWindow::connect_signals\(\))',
    setup_ui_replacement + '\n\n',
    content,
    flags=re.DOTALL
)

content = re.sub(
    r'void MainWindow::setup_styles\(\)\s*\{.*?(?=\nvoid MainWindow::connect_signals\(\))',
    setup_styles_replacement + '\n\n',
    content,
    flags=re.DOTALL
)

with open("qt_client/src/ui/main_window.cpp", "w") as f:
    f.write(content)
print("done")
