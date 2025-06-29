#ifndef WORKER_H
#define WORKER_H
#include<QTcpSocket>
#include <QObject>

class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(QObject *parent = nullptr);

    void handle(QTcpSocket * new_soc);
signals:
};

#endif // WORKER_H
