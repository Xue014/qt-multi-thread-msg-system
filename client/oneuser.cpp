#include "oneuser.h"
#include<QDebug>
#include <QHostAddress>
#include<QFile>
#include <QThread>
#include<QFileInfo>
#include <qmessagebox.h>
#include <QJsonObject>
#include <QJsonDocument>
Oneuser::Oneuser(QString name,QObject *parent)
    : QObject{parent}
{
    //简历连接
    socket = new QTcpSocket(this);
    socket->connectToHost(QHostAddress("127.0.0.1"), 8989);
    connect(socket,&QTcpSocket::connected,this,[=](){
        //连接成功之后，立刻发送一个发件人的姓名
        QThread::sleep(1); // 休眠 1 秒
        Sname = name;
        socket->write(Sname.toUtf8());


    });

    //等待数据的到来
    //emit到主线程上，显示在屏幕上

    //当有消息到达的时候
    connect(socket,&QTcpSocket::readyRead,this,&Oneuser::recemess);


}

void Oneuser::recemess()
{

    //接收到新的消息了 ,有两个可以一个是消息，一个是在线人数.


     QByteArray data = socket->readAll();
    // qDebug()<<data;
    // qDebug()<<"void Oneuser::recemess()";

     if (data.isEmpty())
     {
         qDebug() << "数据是空的";
     }
     else if (!data.isEmpty())
     {



         QJsonDocument doc = QJsonDocument::fromJson(data);
         QJsonObject obj = doc.object();

         QJsonValue recetverID = obj.value("messageType");
         QString firstByte = recetverID.toString();
         // qDebug()<<firstByte;

         if (firstByte == "0")
         {
            emit Mainrecemess(data);

         }
         else if (firstByte == "1")
         {
             emit Mainrecefile(data);
         }
         else if (firstByte == "3") //发送的是在线人数 数组
         {
             // qDebug()<<"firstByte == 3被触发了";
             emit onlineUsign(data);

         }




     }







}
void Oneuser::ReceID(QString currentReceiverId)
{
    ID = currentReceiverId; //全局ID，封装到消息里面
}



void Oneuser::Sendm(QString mess) //发送消息
{

    QString data = mess;

    QString messageType = "0";   // 0 表示消息

    QJsonObject obj;
    obj.insert("messageType",QJsonValue(messageType));
    obj.insert("receiver",QJsonValue(ID));
    obj.insert("sender",QJsonValue(Sname));
    obj.insert("content",QJsonValue(data));

    QJsonDocument doc(obj);

    //就可以再次转成字符串
    QByteArray json = doc.toJson();

    // 使用 write 方法发送数据
    socket->write(json);
    // qDebug()<<json;

    //发送完消息，主线程把文字清楚了
    emit sendok();

}

void Oneuser::sendfile(QString path)
{
    //点击选择文件
    //需要发送文件名和文件大小
    QFileInfo info(path);
    qint64 fileSize = info.size();
    QString sizeString = QString::number(fileSize);
    QString fileName = info.fileName();
    QString suffix = info.suffix();

    QFile file(path);
    file.open(QFile::ReadOnly);//以只读打开
    QByteArray Aline = file.readAll();
    QString data =  QString(Aline);

    QString messageType = "1"; // 协议头：1 表示文件

    QJsonObject obj;
    obj.insert("messageType",QJsonValue(messageType));
    obj.insert("receiver",QJsonValue(ID));
    obj.insert("sender",QJsonValue(Sname));
    obj.insert("size",QJsonValue(sizeString));
    obj.insert("name",QJsonValue(fileName));
    obj.insert("content",QJsonValue(data));
    obj.insert("suffix",QJsonValue(suffix));

    QJsonDocument doc(obj);

    //就可以再次转成字符串
    QByteArray json = doc.toJson();



    socket->write(json);

}
