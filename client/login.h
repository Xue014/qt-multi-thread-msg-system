#ifndef LOGIN_H
#define LOGIN_H

#include <QObject>
#include<QSqlDatabase>

class Login : public QObject
{
    Q_OBJECT
public:
    explicit Login(QObject *parent = nullptr);
    QSqlDatabase db;

signals:
};

#endif // LOGIN_H
