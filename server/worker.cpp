#include "worker.h"
#include <QDebug>

Worker::Worker(QObject *parent)
    : QObject{parent}
{}

void Worker::handle(QTcpSocket * new_soc)
{

    qDebug() << new_soc;



    connect(new_soc, &QTcpSocket::readyRead, [=]() {
        // 读取所有可用的数据
        QByteArray data = new_soc->readAll();

        // 检查数据是否为空
        if (!data.isEmpty()) {
            // 获取第一个字节
            char firstByte = data.at(0);


            if (firstByte == 0) {
                // 第一个字节为 0，处理消息数据
                QByteArray messageData = data.mid(1); // 去掉第一个字节，获取实际的消息数据
                QString message = QString::fromUtf8(messageData);
                qDebug() << "Received message: " << message;
            } else if (firstByte == 1) {
                // 第一个字节为 1，处理文件数据
                QByteArray fileData = data.mid(1); // 去掉第一个字节，获取实际的文件数据
                qDebug() << "Received file data, size: " << fileData.size();
                // 这里可以添加保存文件的逻辑
            } else {
                // 第一个字节不是 0 也不是 1，处理错误情况
                qDebug() << "Invalid data type: " << firstByte;
            }
        }
    });
}
