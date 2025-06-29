#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThread>
#include <QMessageBox>
#include <QThreadPool>
#include "transmit.h"
#include <QMutex>
QJsonArray  MainWindow::array;
QMap<QString, QTcpSocket*> MainWindow::clientIdMap;

QMutex MainWindow::clientIdMapMutex;
// std::vector< Transmit*> g_vecClient;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // setWindowTitle("服务器转发栈");

    server = new QTcpServer(this);

    if (!server->listen(QHostAddress::Any, 8989)) {
        qDebug() << "Server could not start!";
    }
    else {
        qDebug() << "Server started!";
    }

    connect(server, &QTcpServer::newConnection, this, [=]() {
        socket = server->nextPendingConnection();
        Transmit* worker = new Transmit(socket);
        worker->start();
        // g_vecClient.push_back(worker);
    });
    
}

MainWindow::~MainWindow()
{
    delete ui;
}
