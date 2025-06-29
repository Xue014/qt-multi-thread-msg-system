#ifndef USELOGIN_H
#define USELOGIN_H

#include <QMainWindow>
#include<QSqlDatabase>

namespace Ui {
class UseLogin;
}

class UseLogin : public QMainWindow
{
    Q_OBJECT

public:
    explicit UseLogin(QWidget *parent = nullptr);
    ~UseLogin();
    QSqlDatabase db;

private slots:

    void on_zhuce_clicked();

    void on_login_clicked();

private:
    Ui::UseLogin *ui;
signals:
    void login_success(QString name);
    void login_success1(QString name);
    void LoginFail();
    void Renmae();
    void RegisterSuccess();
    void sendmap(const QMap<QString, QString>& map);
};

#endif // USELOGIN_H
