import re

with open("qt_client/src/ui/main_window.cpp", "r") as f:
    text = f.read()

reg_ui_addition = """
    // ============= Register Page =============
    register_widget_ = new QWidget();
    register_widget_->setStyleSheet("background-color: #f3f3f3;");
    QVBoxLayout* reg_main_layout = new QVBoxLayout(register_widget_);
    reg_main_layout->setAlignment(Qt::AlignCenter);
    
    QWidget* reg_card = new QWidget();
    reg_card->setObjectName("CardWidget");
    reg_card->setFixedSize(420, 480);
    QVBoxLayout* reg_layout = new QVBoxLayout(reg_card);
    reg_layout->setSpacing(20);
    reg_layout->setContentsMargins(40, 40, 40, 40);
    
    QLabel* reg_title = new QLabel("账号注册");
    reg_title->setStyleSheet("font-size: 28px; font-weight: 600; color: #1a1a1a;");
    reg_title->setAlignment(Qt::AlignCenter);
    reg_layout->addWidget(reg_title);
    
    QGroupBox* reg_form_group = new QGroupBox();
    QFormLayout* reg_form_layout = new QFormLayout(reg_form_group);
    reg_form_layout->setSpacing(15);
    
    reg_username_input_ = new QLineEdit();
    reg_username_input_->setPlaceholderText("请输入要注册的用户名");
    
    reg_password_input_ = new QLineEdit();
    reg_password_input_->setPlaceholderText("请输入密码");
    reg_password_input_->setEchoMode(QLineEdit::Password);
    
    reg_password_confirm_input_ = new QLineEdit();
    reg_password_confirm_input_->setPlaceholderText("请再次输入密码");
    reg_password_confirm_input_->setEchoMode(QLineEdit::Password);
    
    reg_form_layout->addRow("用户名:", reg_username_input_);
    reg_form_layout->addRow("密  码:", reg_password_input_);
    reg_form_layout->addRow("确认密码:", reg_password_confirm_input_);
    
    reg_layout->addWidget(reg_form_group);
    
    reg_button_ = new QPushButton("注 册");
    reg_button_->setMinimumHeight(40);
    reg_button_->setObjectName("PrimaryButton");
    reg_layout->addWidget(reg_button_);
    
    QPushButton* switch_login_btn = new QPushButton("已有账号？返回登录");
    switch_login_btn->setStyleSheet("background: transparent; color: #005fb8; border: none; text-decoration: underline;");
    switch_login_btn->setCursor(Qt::PointingHandCursor);
    reg_layout->addWidget(switch_login_btn);
    reg_layout->addStretch();
    reg_main_layout->addWidget(reg_card);
    stacked->addWidget(register_widget_);
"""

# Inject register page into setup_ui
if "Register Page" not in text:
    text = text.replace("stacked->addWidget(login_widget_);", "stacked->addWidget(login_widget_);\n" + reg_ui_addition)

# Inject connections
connections = r"""
    connect(switch_register_btn, &QPushButton::clicked, this, &MainWindow::on_switch_to_register_clicked);
    connect(switch_login_btn, &QPushButton::clicked, this, &MainWindow::on_switch_to_login_clicked);
    connect(reg_button_, &QPushButton::clicked, this, &MainWindow::on_register_clicked);
"""
if "on_switch_to_register_clicked" not in text:
    text = text.replace("void MainWindow::connect_signals() {", "void MainWindow::connect_signals() {\n" + connections)
    # also we need to find the definition of the buttons.
    # To fix scope issues with switch_register_btn in lambda/connect, we should add slots.

# Implement slots
slots_impl = """
void MainWindow::show_register_page() {
    ((QStackedWidget*)centralWidget())->setCurrentWidget(register_widget_);
}

void MainWindow::on_switch_to_register_clicked() {
    reg_username_input_->clear();
    reg_password_input_->clear();
    reg_password_confirm_input_->clear();
    show_register_page();
}

void MainWindow::on_switch_to_login_clicked() {
    show_login_page();
}

void MainWindow::on_register_clicked() {
    QString username = reg_username_input_->text().trimmed();
    QString password = reg_password_input_->text();
    QString confirm = reg_password_confirm_input_->text();
    
    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "提示", "用户名和密码不能为空！");
        return;
    }
    
    if (password != confirm) {
        QMessageBox::warning(this, "提示", "两次输入的密码不一致！");
        return;
    }
    
    // Save to local SQLite database
    QSqlQuery query;
    query.prepare("SELECT username FROM users WHERE username = :username");
    query.bindValue(":username", username);
    if (query.exec() && query.next()) {
        QMessageBox::warning(this, "提示", "该用户名已经被注册了！");
        return;
    }
    
    query.prepare("INSERT INTO users (username, password) VALUES (:username, :password)");
    query.bindValue(":username", username);
    query.bindValue(":password", password); // In production, add salt & hash here
    if (query.exec()) {
        QMessageBox::information(this, "成功", "注册成功！请登录。");
        username_input_->setText(username);
        password_input_->clear();
        show_login_page();
    } else {
        QMessageBox::critical(this, "错误", "注册写入数据库失败: " + query.lastError().text());
    }
}
"""

if "void MainWindow::on_register_clicked()" not in text:
    text += "\n" + slots_impl

# Change language to Chinese
text = text.replace('"Contacts"', '"联系人"')
text = text.replace('"Groups"', '"群组"')
text = text.replace('"Create Group"', '"创建群组"')
text = text.replace('"Join Group"', '"加入群组"')
text = text.replace('"Send"', '"发送"')
text = text.replace('"FluentNav UI"', '"欢迎使用 IM"')
text = text.replace('"Select a Contact or Group"', '"请选择侧边栏的联系人或群组开始聊天"')
text = text.replace('"Type your message here..."', '"在此输入消息，点击发送..."')
text = text.replace('"FluentUI Chat Experience"', '"现代 IM 聊天系统"')
text = text.replace('"Recent updates and modern controls incorporated in chat.\\nSelect a conversation to begin."', '"全平台支持的高效通讯应用。\\n请在左侧选择对话以开始。"')
text = text.replace('"User: Not logged in"', '"用户: 尚未登录"')

with open("qt_client/src/ui/main_window.cpp", "w") as f:
    f.write(text)

print("UI patched")
