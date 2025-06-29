#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QTcpServer>
#include<QTcpSocket>
#include <QMap>
#include <QMutex>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QTcpServer *server;
    QTcpSocket *socket;

    QList<QTcpSocket*> m_lstClients;

    static QJsonArray array;
    static QMap<QString, QTcpSocket*> clientIdMap;
    static QMutex clientIdMapMutex;
protected:
signals:
    void newsock(QTcpSocket *sock);

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
