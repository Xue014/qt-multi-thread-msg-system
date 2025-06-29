#ifndef ONEUSER_H
#define ONEUSER_H

#include<QTcpSocket>
#include <QObject>

class Oneuser : public QObject
{
    Q_OBJECT
public:
    explicit Oneuser(QString name,QObject *parent = nullptr);
    QTcpSocket *socket;
    QString  ID;
     void recemess();
    QString Sname;

public slots:
    void Sendm(QString mess);
    void sendfile(QString path);
    void ReceID(QString currentReceiverId);
signals:
    void sendok();
    void Mainrecemess(QByteArray FmessageData);
    void Mainrecefile(QByteArray FmessageData);

    void onlineUsign(QByteArray FmessageData);
};

#endif // ONEUSER_H
