import re

with open("qt_client/CMakeLists.txt", "r") as f:
    cmake_text = f.read()

if "Sql" not in cmake_text:
    cmake_text = cmake_text.replace("Core Gui Widgets", "Core Gui Widgets Sql")
    with open("qt_client/CMakeLists.txt", "w") as f:
        f.write(cmake_text)

with open("qt_client/src/ui/main_window.hpp", "r") as f:
    hpp_text = f.read()

if "QWidget* register_widget_;" not in hpp_text:
    hpp_text = hpp_text.replace("QWidget* login_widget_;", 
        "QWidget* login_widget_;\n    QWidget* register_widget_;\n"
        "    QLineEdit* reg_username_input_;\n"
        "    QLineEdit* reg_password_input_;\n"
        "    QLineEdit* reg_password_confirm_input_;\n"
        "    QPushButton* reg_button_;")
    hpp_text = hpp_text.replace("void show_login_page();", 
        "void show_login_page();\n"
        "    void show_register_page();\n"
        "    void init_database();")
    hpp_text = hpp_text.replace("void on_login_clicked();", 
        "void on_login_clicked();\n"
        "    void on_register_clicked();\n"
        "    void on_switch_to_register_clicked();\n"
        "    void on_switch_to_login_clicked();")
    with open("qt_client/src/ui/main_window.hpp", "w") as f:
        f.write(hpp_text)

with open("qt_client/src/ui/main_window.cpp", "r") as f:
    cpp_text = f.read()

# Add QSqlDatabase headers if not there
if "QSqlDatabase" not in cpp_text:
    cpp_text = cpp_text.replace("#include <QDateTime>", "#include <QDateTime>\n#include <QSqlDatabase>\n#include <QSqlQuery>\n#include <QSqlError>\n#include <QDir>")

# Implement database initialization
db_impl = """
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
"""
if "void MainWindow::init_database()" not in cpp_text:
    cpp_text = cpp_text.replace("MainWindow::MainWindow", db_impl + "\nMainWindow::MainWindow")

# Add init_database to constructor
if "init_database();" not in cpp_text:
     cpp_text = re.sub(
         r'setup_ui\(\);\s+setup_styles\(\);\s+connect_signals\(\);',
         r'setup_ui();\n    setup_styles();\n    connect_signals();\n    init_database();',
         cpp_text
     )

with open("qt_client/src/ui/main_window.cpp", "w") as f:
    f.write(cpp_text)

print("Headers and DB patch applied.")
