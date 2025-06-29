#include "mainwindow.h"
#include "uselogin.h"
#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    UseLogin *use = new UseLogin();   // 注意他的释放时机
    use->show(); // 显示登录界面

    MainWindow *mainWindow = nullptr;

    QObject::connect(use, &UseLogin::login_success, [&](QString username) {
        if (!mainWindow) {
            mainWindow = new MainWindow(use);
            QObject::connect(mainWindow, &MainWindow::destroyed, [use]() {
                delete use;
            });
        }
        mainWindow->show();
        mainWindow->setWindowTitle(username);
        use->hide();
    });

    QObject::connect(use, &UseLogin::LoginFail, [=]() {
        QMessageBox::information(nullptr, "用户登录", "密码或用户名错误");
    });

    QObject::connect(use, &UseLogin::Renmae, [=]() {
        QMessageBox::information(nullptr, "用户注册", "用户名已存在");
    });

    QObject::connect(use, &UseLogin::RegisterSuccess, [=]() {
        QMessageBox::information(nullptr, "用户注册", "注册成功,请重新登录");
    });

    return a.exec();
}
