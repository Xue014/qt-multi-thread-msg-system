#include "login.h"
#include <QSqlDatabase>
#include<QMessageBox>
#include<QDebug>
Login::Login(QObject *parent)
    : QObject{parent}
{
    db = QSqlDatabase::addDatabase("QMYSQL");//加载MYSQL数据库驱动

    db.setDatabaseName("qtdatabase");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("12345ssdlH");

    if(db.open())
    {
        qDebug()<<"连接数据库成功";
    }

    // else
    // {
    //     QMessageBox::warning(this,"连接提示","连接失败");
    // }
}
