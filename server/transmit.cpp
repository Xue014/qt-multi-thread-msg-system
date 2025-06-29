#include "transmit.h"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include<QMutexLocker>
#include "mainwindow.h"

Transmit::Transmit(QTcpSocket* socket)
{
    m_socket = socket;

    // QMetaObject::Connection connection;
    // connection = QObject::connect(m_socket, &QTcpSocket::readyRead, [this, connection]() mutable
    // {
    QObject::connect(m_socket, &QTcpSocket::readyRead,[=]()
    {
        if (m_meID.isEmpty())
        {

            m_meID = m_socket->readAll();//用户上仙


            QMutexLocker locker(&MainWindow::clientIdMapMutex);
            MainWindow::clientIdMap[m_meID] = m_socket;



            MainWindow::array.append(m_meID); //添加在线用户
            QJsonObject objarray;
            objarray.insert("onlineUser",MainWindow::array);
            objarray.insert("messageType","3");
            QJsonDocument docarray(objarray);
            QByteArray DataOnlineUser = docarray.toJson();




            QMap<QString, QTcpSocket*>::iterator it;
            for (it = MainWindow::clientIdMap.begin(); it != MainWindow::clientIdMap.end(); ++it)
            {
                QString key = it.key();
                QTcpSocket* value = it.value();
                value->write(DataOnlineUser);//给每一个在线都发送..确保了实时刷新了
                qDebug() << "Key: " << key << ", Value (QTcpSocket pointer): " << value;
            }
        }
    });


            // QObject::disconnect(connection);


    // });

    // 连接 disconnected 信号，当客户端断开连接时从映射中移除
    QObject::connect(m_socket, &QTcpSocket::disconnected, [this]()
    {
        QMutexLocker locker(&MainWindow::clientIdMapMutex);
        if (MainWindow::clientIdMap.contains(m_meID))
        {
            MainWindow::clientIdMap.remove(m_meID);
            //移除在线用户
            for (int i = MainWindow::array.size() - 1; i >= 0; --i)
            {
                if (MainWindow::array.at(i) == m_meID) {
                    MainWindow::array.removeAt(i);
                }
            }


        }
    });
}


void Transmit::run() //每次新客户端连接都默认调用的
{



    if (m_socket) {
        handle(m_socket);
    }
}

void Transmit::handle(QTcpSocket* new_soc)
{
    if (new_soc->state() != QAbstractSocket::ConnectedState)
    {
        qDebug() << "new_soc is not connected.";
        return;
    }


    QObject::connect(new_soc, &QTcpSocket::readyRead, [this, new_soc]()
    {
        QByteArray data = new_soc->readAll();
        if (data.isEmpty())
        {
            // qDebug() << "数据是空的";
            return;
        }





        QJsonDocument doc = QJsonDocument::fromJson(data);
        QJsonObject obj = doc.object();

        QJsonValue recetverID = obj.value("receiver");//找到接收方
        QString strValue = recetverID.toString();
        QByteArray useID1 = strValue.toUtf8(); //接收方..





        // 加锁保护共享资源
        QMutexLocker locker(&MainWindow::clientIdMapMutex);
        if (MainWindow::clientIdMap.contains(useID1))
        {
            // qDebug() << json;

            QTcpSocket* targetSocket = MainWindow::clientIdMap[useID1];
            // 检查目标套接字是否存活（防止空指针或已断开的套接字）
            if (targetSocket && targetSocket->state() == QAbstractSocket::ConnectedState)
            {
                targetSocket->write(data); // 发送消息
            }
            else
            {
                MainWindow::clientIdMap.remove(useID1); // 移除无效的套接字
                qDebug() << "目标客户端已断开连接，ID:" << useID1;
            }
        }
        else if(useID1 == "BroadcastMessages") // 群发消息
        {


            QMap<QString, QTcpSocket*>::iterator it;
            for (it = MainWindow::clientIdMap.begin(); it != MainWindow::clientIdMap.end(); ++it)
            {
                QString clientId = it.key();
                QTcpSocket* value = it.value();

                if (value && value->state() == QAbstractSocket::ConnectedState)
                {
                    if (clientId != m_meID) {
                        if (value->write(data) == -1) {
                            qDebug() << "群发消息失败 to " << clientId;

                        }

                    }
                }
                else
                {
                    // 移除无效的客户端 <<<<<<<<
                    MainWindow::clientIdMap.remove(clientId);
                    // MainWindow::array.removeAll(clientId);
                    qDebug() << "群发时发现无效客户端，已移除: " << clientId;

                }
            }


        }
        else
        {
            qDebug() << "接收方 ID 不存在:" << useID1;
        }
    });
}
