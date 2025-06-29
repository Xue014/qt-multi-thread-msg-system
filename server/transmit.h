#ifndef TRANSMIT_H
#define TRANSMIT_H

#include <QThread>
#include <QRunnable>
#include <QTcpSocket>
#include <QJsonArray>

struct SLoginPacket
{

};
struct SLoginPacketAnwser
{

};

class Transmit : public QThread
{
public:
    explicit Transmit(QTcpSocket *socket);
    void run() override;
    void handle(QTcpSocket * new_soc);



private:
    QTcpSocket *m_socket;
    QString m_meID;
};

#endif // TRANSMIT_H
