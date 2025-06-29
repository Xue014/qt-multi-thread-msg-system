#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QJsonValue>
#include "uselogin.h"
#include "ChatMessageDelegate.h"
#include<mylistwidgetitem.h>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(UseLogin *use, QWidget *parent = nullptr);
    ~MainWindow();
    // void addUserToList(const QString &iconPath, const QString &username);
    void addUserToList(const QString &iconPath, const QString &userId);
    void clearwin();
    void onTabClosed(int index);
    void createChatTab(const QString &userId);
    MyListWidgetItem *MYitem;
    QString USERNAME;


    void handleFileItemClick(QListWidgetItem *item);
private slots:
    void on_sendfile_clicked();

    void on_sendmes_clicked();
    void nfriend(const QMap<QString, QString>& map);
    void onlineu(QByteArray onlineData);
    void on_img_clicked();
    // void clickedLeftItem(int index);

signals:
    void sendmessage(QString mess );
    void sendfilePath(QString path);
    void sendID( QString currentReceiverId);
    // void name(Qstring name);

private:
    Ui::MainWindow *ui;
    UseLogin *m_use;
    QString currentReceiverId; // 当前选中的接收方用户ID

    QMap<QString, QPair<QListWidget*, QWidget*>> chatSessions; // ID到聊天窗口和标签页的映射
    QTabWidget *chatTabs;
    QString iconPath;
    QJsonValue onlineUserValue;
    int count;




};
#endif // MAINWINDOW_H
