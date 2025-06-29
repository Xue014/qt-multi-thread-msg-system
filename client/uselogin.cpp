#include "uselogin.h"
#include "ui_uselogin.h"
#include <QSqlDatabase>
#include<QMessageBox>
#include<QDebug>
#include <QSqlQuery>

UseLogin::UseLogin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::UseLogin)
{


    ui->setupUi(this);
    setWindowTitle("用户登录");
    this->setWindowIcon(QIcon(":/image/icon.png"));
    //页面初始化
    //添加背景图....
    // 添加背景图，设置背景颜色为蓝色，设置字体大小和样式
    ui->welcom->setStyleSheet("color: blue; font-size: 40px; font-family: Arial;");

    ui->login->setStyleSheet("color: blue; font-size: 14px; font-family: Arial;");
    ui->name_2->setStyleSheet("color: blue; font-size: 14px; font-family: Arial;");
    ui->password_2->setStyleSheet("color: blue; font-size: 14px; font-family: Arial;");
    ui->zhuce->setStyleSheet("color: blue; font-size: 14px; font-family: Arial;");

    // QPixmap pixmap=QPixmap(":/image/background.jpg").scaled(this->size());
    // QPalette palette;
    // //设置主窗口背景图片
    // palette.setBrush(QPalette::Window,QBrush(pixmap));
    // this->setPalette(palette);







    db = QSqlDatabase::addDatabase("QMYSQL");//加载MYSQL数据库驱动

    db.setDatabaseName("qtdatabase");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("12345ssdlH");

    if(db.open())
    {
        qDebug()<<"连接数据库成功";
    }

}

UseLogin::~UseLogin()
{
    delete ui;
}




void UseLogin::on_zhuce_clicked()
{
    //点击注册  弹窗注册成功，需要重新登录才可以进去

    //点击了登录，登录成功再发信号，携带登陆者的用户名
    QString name = ui->name->text();
    QString password = ui->password->text();
    QSqlQuery query, query1;

    // 如果用户名重复弹窗
    query.prepare("SELECT * FROM users WHERE username = :name");
    query.bindValue(":name", name);
    if (query.exec() && query.next())
    {
        // 有这个姓名，不让注册
        emit Renmae();
    }
    else
    {
        query1.prepare("INSERT INTO users (username, password) VALUES (:name, :password)");
        query1.bindValue(":name", name);
        query1.bindValue(":password", password);
        if (query1.exec())
        {
            // 弹窗注册成功，请重新登录
            emit RegisterSuccess();
            ui->name->setText("");
            ui->password->setText("");
        }
    }
}

void UseLogin::on_login_clicked()
{
    //点击了登录，登录成功再发信号，携带登陆者的用户名
    QString name = ui->name->text();
    QString password = ui->password->text();
    //进行查询
    QSqlQuery query;
    //要预处理的 SQL 语句，其中可以包含占位符，用于后续绑定参数。:name 和 :password 是占位符，
    query.prepare("SELECT * FROM users  WHERE username=:name AND password = :password");
    //bindValue() 方法用于将具体的值绑定到预处理 SQL 语句中的占位符上。这样可以避免直接将用户输入的值拼接到 SQL 语句中，从而防止 SQL 注入攻击
    query.bindValue(":name",name);
    query.bindValue(":password",password);

    if (query.exec() && query.next())
    {
        //登录成功携带用户名过去
        emit login_success(name);
        emit login_success1(name);
        //获取好友的的username和headimg
        QSqlQuery queryfriend;
        queryfriend.prepare("SELECT friend_username,friend_avatar FROM friends WHERE user_name = :name");
        queryfriend.bindValue(":name",name);
        QMap<QString,QString> map;
        if(queryfriend.exec())
        {

            while(queryfriend.next())
            {
                QString friendUsername = queryfriend.value(0).toString();
                QString friendUserhead= queryfriend.value(1).toString();
                // qDebug()<<friendUsername;
                // qDebug()<<friendUserhead;
                map[friendUsername] =friendUserhead;


            }
        }
        else
        {
            qDebug()<<"exec失败";
        }
        //等待一个信号，然后把map发送吗
        emit sendmap(map);




    }
    else
    {
        //登录失败
        emit LoginFail();
        qDebug()<<name;
        qDebug()<<password;
    }
}

