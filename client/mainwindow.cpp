#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QListWidgetItem>
#include<QVector>
#include <Qthread>
#include <qfiledialog.h>
#include"oneuser.h"
#include<QFile>
#include<QDebug>
#include<QFileDialog>
#include<QMessageBox>
#include<uselogin.h>
#include <QJsonDocument>
#include <QJsonObject>
#include<QFileInfo>
#include <QJsonArray>
#include<mylistwidgetitem.h>
// 全局变量定义
QMap<int, QByteArray> fileDataMap;  // 文件数据
int fileIndexCounter = 0;           //文件索引计数器


MainWindow::MainWindow(UseLogin *use, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), m_use(use)
{
    ui->setupUi(this);
    setFixedSize(1152, 817);
    this->setWindowIcon(QIcon(":/image/icon.png"));
    chatTabs = ui->chatTabs;

    // 连接标签关闭信号
    connect(chatTabs, &QTabWidget::tabCloseRequested, this, &MainWindow::onTabClosed);

    //按钮的背景色设置成透明

    ui->img->setStyleSheet("QPushButton { background-color: transparent; }");

    ui->sp->setStyleSheet("QPushButton { background-color: transparent; }");
    ui->yy->setStyleSheet("QPushButton { background-color: transparent; }");
    ui->sendfile->setStyleSheet("QPushButton { background-color: transparent; }");
    ui->chatbtn->setStyleSheet("QPushButton { background-color: transparent; }");
    ui->friend_2->setStyleSheet("QPushButton { background-color: transparent; }");
    // ui->massText->setStyleSheet("QPushButton { background-color: transparent; }");

    ui->cebianlian->setStyleSheet("QTextEdit { background:#888888 ; }");

    ui->useall->setIconSize(QSize(40, 40)); // 设置图标大小为 128x128
    ui->useall->setUniformItemSizes(true); // 确保所有条目大小一致
    QSize itemSize(150, 70); // 设置每个条目的大小
    ui->useall->setGridSize(itemSize);
    ui->useall->setStyleSheet("QListWidget { background: #F0F0F0; }");//浅灰色#F8F8F8
    ui->sendmes->setEnabled(false);
    ui->CHAT->setStyleSheet("font-family: 微软雅黑; "
                            "font-size: 8pt; "
                            "font-weight: bold; "
                            "color: #333333;");

    ui->choosname->setStyleSheet("font-family: 微软雅黑; "
                                 "font-size: 14pt; "
                                 "font-weight: bold; "
                                 "color: #333333;");
    ui->yy->setVisible(false);
    ui->sp->setVisible(false);
    ui->img->setVisible(false);







    connect(m_use, &UseLogin::login_success1, this, [&](QString username) {//m_use是uselogin的只针对性
        USERNAME = username; //被成功赋值了
        //创建子线程,moveToThread
        //创建线程对象
        QThread *t = new QThread;
        //创建任务对象
        // qDebug()<<USERNAME;//这里就看不见了
        Oneuser *worker = new Oneuser(USERNAME);
        //移动到线程里面，（任务函数再执行的时候，就会再线程t里面）
        worker->moveToThread(t);

        //接收信号所有好友的名称和头像。uselogin里面去获取
        connect(m_use,&UseLogin::sendmap,this,&MainWindow::nfriend);//添加好友到列表
        connect(this,&MainWindow::sendmessage,worker,&Oneuser::Sendm); //点击发送消息后进入子线程
        connect(this,&MainWindow::sendfilePath,worker,&Oneuser::sendfile);//发送文件
        connect(worker,&Oneuser::onlineUsign,this,&MainWindow::onlineu);//发送在线人数
        //点击用户头像以后,选中id

        connect(ui->useall, &QListWidget::itemClicked, this, [this](QListWidgetItem *item) {
            ui->sendmes->setEnabled(true);
            currentReceiverId = item->data(Qt::UserRole).toString();
            createChatTab(currentReceiverId); // 创建或切换到对应标签页
            ui->choosname->setText(currentReceiverId);
            emit sendID(currentReceiverId);
        });
        connect(this,&MainWindow::sendID,worker,&Oneuser::ReceID);


        //接收到消息
        connect(worker,&Oneuser::Mainrecemess,this,[=](QByteArray Data){

            QJsonDocument doc = QJsonDocument::fromJson(Data);
            QJsonObject obj = doc.object();


            //发送者
            QJsonValue SenderIdsonValue = obj.value("sender");
            QString senderId = SenderIdsonValue.toString();


            //消息
            QJsonValue messagesonValue = obj.value("content");
            QString message = messagesonValue.toString();


            if (chatSessions.contains(senderId)) { //存在回话  应该看接收方是不是存在对话啊
                QListWidget *chatList = chatSessions[senderId].first;
                QListWidgetItem *item = new QListWidgetItem(message);
                item->setData(Qt::UserRole + 1, false); // 标记为接收消息  用于为该条目设置自定义数据。
                item->setData(Qt::UserRole + 2, QDateTime::currentDateTime()); // 添加时间戳
                chatList->addItem(item);
                chatList->scrollToBottom();
            }
            else {
                createChatTab(senderId);

                ui->choosname->setText(senderId);
                QListWidget *chatList = chatSessions[senderId].first;
                QListWidgetItem *item = new QListWidgetItem(message); //QListWidgetItem 是 Qt 框架里的一个类，主要用于在 QListWidget 控件里代表单个条目
                item->setData(Qt::UserRole + 1, false); // 标记为接收消息
                chatList->addItem(item);
                chatList->scrollToBottom();//将聊天列表的滚动条滚动到列表底部
            }
        });





        //有文件到达的时候
        connect(worker,&Oneuser::Mainrecefile,this,[=](QByteArray Data){
            QJsonDocument doc = QJsonDocument::fromJson(Data);
            QJsonObject obj = doc.object();

            //发送者
            QJsonValue SenderIdsonValue = obj.value("sender");
            QString senderId = SenderIdsonValue.toString();

            //文件大小
            QJsonValue sizesonValue = obj.value("size");
            QString size = sizesonValue.toString();

            //文件名
            QJsonValue nameValue = obj.value("name");
            QString name = nameValue.toString();

            //文件内容
            QJsonValue dataValue = obj.value("content");
            QString datasing = dataValue.toString();
            QByteArray data = datasing.toLocal8Bit();

            //文件后缀
            QJsonValue suffixValue = obj.value("suffix");
            QString suffix = suffixValue.toString();

            QString iconPath;
            if(suffix == "txt")//文本文档
            {
                iconPath=":/image/txt.png";
            }
            else if(suffix == "docx"||suffix == "doc")//word
            {
                iconPath = ":/image/WORD.png";
            }
            else {
                iconPath = ":/image/file.png"; // 默认文件图标
            }

            QString itemText = QString("%1||%2%3").arg(name).arg(size).arg("b");

            QListWidget *chatList = chatSessions[senderId].first;

            // 存储文件数据并获取唯一索引
            int currentFileIndex = ++fileIndexCounter;
            fileDataMap[currentFileIndex] = data;

            if (chatSessions.contains(senderId)) {
                MyListWidgetItem *fileItem = new MyListWidgetItem(QIcon(iconPath), itemText);
                fileItem->setIndex(currentFileIndex); // 设置唯一索引

                fileItem->setData(Qt::UserRole + 1, false); // 标记为接收消息
                fileItem->setData(Qt::UserRole + 2, QDateTime::currentDateTime()); // 添加时间戳


                QListWidgetItem *listItem = new QListWidgetItem();
                // listItem->setSizeHint(QSize(150, 50)); // 设置项大小
                chatList->addItem(listItem);
                chatList->setItemWidget(listItem, fileItem);

                // 连接文件项点击事件
                connect(fileItem, &MyListWidgetItem::listItemClicked, this, [this,chatList](int index) {
                    if (fileDataMap.contains(index)) {

                        QString path = QFileDialog::getSaveFileName(this, "保存文件", "", "所有文件 (*.*)");

                        if (!path.isEmpty()) {
                            QFile file(path);
                            if (file.open(QIODevice::WriteOnly)) {
                                file.write(fileDataMap[index]);
                                file.close();
                                QMessageBox::information(this, "成功", "文件保存成功！");
                            } else {
                                QMessageBox::warning(this, "错误", "无法打开文件进行写入！");
                            }
                        }
                    }
                });

                chatList->scrollToBottom();
            }
            else {
                createChatTab(senderId);
                if(chatSessions.contains(senderId)) {
                    ui->choosname->setText(senderId);

                    MyListWidgetItem *fileItem = new MyListWidgetItem(QIcon(iconPath), itemText);
                    fileItem->setIndex(currentFileIndex); // 设置唯一索引

                    fileItem->setData(Qt::UserRole + 1, false); // 标记为接收消息
                    fileItem->setData(Qt::UserRole + 2, QDateTime::currentDateTime()); // 添加时间戳


                    QListWidgetItem *listItem = new QListWidgetItem();
                    listItem->setSizeHint(QSize(150, 50)); // 设置项大小
                    chatList->addItem(listItem);
                    chatList->setItemWidget(listItem, fileItem);

                    // 连接文件项点击事件
                    connect(fileItem, &MyListWidgetItem::listItemClicked, this, [this,chatList](int index) {
                        if (fileDataMap.contains(index)) {

                            QString path = QFileDialog::getSaveFileName(this, "保存文件", "", "所有文件 (*.*)");

                            if (!path.isEmpty()) {
                                QFile file(path);
                                if (file.open(QIODevice::WriteOnly)) {
                                    file.write(fileDataMap[index]);
                                    file.close();
                                    QMessageBox::information(this, "成功", "文件保存成功！");
                                } else {
                                    QMessageBox::warning(this, "错误", "无法打开文件进行写入！");
                                }
                            }
                        }
                    });

                    chatList->scrollToBottom();
                }
                else {
                    qDebug()<<"chatSessions.contains(senderId)创建失败！";
                }
            }
        });




        t->start();//执行子线程

    });


}



int count = 0;

void MainWindow::onlineu(QByteArray onlineData) //获取在线人数 成功
{
    // qDebug()<<"进入函数void MainWindow::onlineu(QByteArray onlineData)了";
    QJsonDocument doc = QJsonDocument::fromJson(onlineData);
    QJsonObject obj = doc.object();

    //在线人数是一个数组
    onlineUserValue  = obj.value("onlineUser");

    QJsonArray onlineUserArray = onlineUserValue.toArray();
    // for(const auto& user : onlineUserArray)
    // {
    //
    // }

    // count++;
    // qDebug()<<QString("我进来啦%1").arg(count);

    for (int i = 0; i < ui->useall->count(); ++i)
    {
        // qDebug()<< ui->useall->count();
        QListWidgetItem *item = ui->useall->item(i);
        QString userId = item->data(Qt::UserRole).toString();
        QString pathicon = item->data(Qt::UserRole+8).toString();
        // qDebug()<<userId;

        for(const auto& user : onlineUserArray)
        {
            // qDebug()<<user.toString();
            if(user.toString()==userId)
            {


                //头像设置成彩色
                item->setIcon(QIcon(pathicon));
            }
        }
    }






}

//获取所有的用户的id
//
void MainWindow::nfriend(const QMap<QString, QString>& map)
{
    // qDebug()<<"nfriend";
    for (auto it = map.constBegin(); it != map.constEnd(); ++it) {
        // qDebug() << "Key:" << it.key() << "Value:" << it.value();
        addUserToList(it.value(),it.key());
    }
}


void MainWindow::addUserToList(const QString &iconPath, const QString &userId) //初始化用户列表
{
    // 加载原始图标
    QIcon originalIcon(iconPath);

    // 创建灰度版本的图标
    QIcon grayIcon;
    if (!originalIcon.isNull()) {
        // 获取图标中默认状态的像素图
        QPixmap originalPixmap = originalIcon.pixmap(50, 50);

        // 创建灰度版本   ？？？？？
        QImage grayImage = originalPixmap.toImage();
        for (int y = 0; y < grayImage.height(); ++y) {
            for (int x = 0; x < grayImage.width(); ++x) {
                QRgb pixel = grayImage.pixel(x, y);
                int gray = qGray(pixel);
                grayImage.setPixel(x, y, qRgba(gray, gray, gray, qAlpha(pixel)));
            }
        }

        // 从灰度图像创建新图标
        grayIcon = QIcon(QPixmap::fromImage(grayImage));
    } else {
        // 如果图标加载失败，使用原始图标（或设置默认图标）
        grayIcon = originalIcon;
    }

    // 创建列表项并设置灰度图标和文本
    if(userId == "BroadcastMessages")
    {
        QListWidgetItem *item = new QListWidgetItem(originalIcon, userId);
        // 将 userId 存储在 item 的 Qt::UserRole 中
        item->setData(Qt::UserRole, userId);
        item->setData(Qt::UserRole+8, iconPath);
        ui->useall->addItem(item);
    }
    else
    {
        QListWidgetItem *item = new QListWidgetItem(grayIcon, userId);
        // 将 userId 存储在 item 的 Qt::UserRole 中
        item->setData(Qt::UserRole, userId);
        item->setData(Qt::UserRole+8, iconPath);
        ui->useall->addItem(item);
    }


}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_sendfile_clicked()//发送文件
{
    // qDebug()<<"我点击了发送文件";
    //点击发送文件
    //选择文件获取路径，
    //点击选择文件
    QString path = QFileDialog::getOpenFileName();
    if (!path.isEmpty()) {
        emit sendfilePath(path); // 传递路径到子线程
    }
    QFileInfo info(path);
    qint64 fileSize = info.size();
    QString sizeString = QString::number(fileSize);

    QString suffix = info.suffix();

    QString fileName = info.fileName();
    QString iconPath;
    if(suffix == "txt")//文本文档
    {
        iconPath=":/image/txt.png";
    }
    else if(suffix == "docx"||suffix == "doc")
    {
        iconPath = ":/image/WORD.png";
    }
    QString itemText = QString("%1||%2%3").arg(fileName).arg(sizeString).arg("b");

    if (chatSessions.contains(currentReceiverId)) { //存在回话
        QListWidget *chatList = chatSessions[currentReceiverId].first;

        QListWidgetItem *item = new QListWidgetItem(QIcon(iconPath), itemText);
        item->setData(Qt::UserRole + 1, true);
        item->setData(Qt::UserRole + 2, QDateTime::currentDateTime()); // 添加时间戳
        chatList->addItem(item);
        chatList->scrollToBottom();
    }
    else {
        // qDebug()<<"我再..";
        createChatTab(currentReceiverId);
        QListWidget *chatList = chatSessions[currentReceiverId].first;

        QListWidgetItem *item = new QListWidgetItem(QIcon(iconPath), itemText);
        item->setData(Qt::UserRole + 1, true); // 标记为接收消息  用于为该条目设置自定义数据。
        item->setData(Qt::UserRole + 2, QDateTime::currentDateTime()); // 添加时间戳
        chatList->addItem(item);
        chatList->scrollToBottom();

    }


}






//点击发送按钮,我是发送的，创建页面的就是接收的了，所有应该看接收消息的人有没有存在了，当前客户端上接收方一定存在，因为我点他的头像了
void MainWindow::on_sendmes_clicked() {
    QString mess = ui->message->toPlainText();
    // qDebug()<<currentReceiverId;
    if (currentReceiverId !="BroadcastMessages")//说明不是群发，
    {
        QListWidget *chatList = chatSessions[currentReceiverId].first;

        QListWidgetItem *item = new QListWidgetItem(mess);
        item->setData(Qt::UserRole + 1, true); // 标记为发送消息
        item->setData(Qt::UserRole + 2, QDateTime::currentDateTime()); // 添加时间戳
        chatList->addItem(item);
        chatList->scrollToBottom();

        emit sendmessage(mess);
    }
    else if(currentReceiverId =="BroadcastMessages")//群发，就给所有在线用户发消息,给所有在线用户添加，但是把，在线用户
    {
        // qDebug()<<"进入群发1";
        if(!onlineUserValue.isNull())
        {
            QJsonArray onlineUserArray = onlineUserValue.toArray();
            for (const auto& user : onlineUserArray) //添加聊天记录的
            {
                // qDebug()<<user.toString();

                if (chatSessions.contains(user.toString())) { //存在回话  应该看接收方是不是存在对话啊
                    QListWidget *chatList = chatSessions[user.toString()].first;
                    QListWidgetItem *item = new QListWidgetItem(mess);
                    item->setData(Qt::UserRole + 1, true);
                    item->setData(Qt::UserRole + 2, QDateTime::currentDateTime()); // 添加时间戳
                    chatList->addItem(item);
                    chatList->scrollToBottom();
                }
                else {
                    createChatTab(user.toString());
                    // ui->choosname->setText(user.toString());
                    QListWidget *chatList = chatSessions[user.toString()].first;
                    QListWidgetItem *item = new QListWidgetItem(mess); //QListWidgetItem 是 Qt 框架里的一个类，主要用于在 QListWidget 控件里代表单个条目
                    item->setData(Qt::UserRole + 1, true);
                    chatList->addItem(item);
                    chatList->scrollToBottom();//将聊天列表的滚动条滚动到列表底部
                }

            }
        }



        emit sendmessage(mess);
    }

    ui->message->clear();
}


//QTabWidget(QWidget(QListWidget))
void MainWindow::createChatTab(const QString &userId) {

    if (!chatSessions.contains(userId)) {
        QListWidget *chatList = new QListWidget();
        chatList->setStyleSheet("QListWidget { background: #F8F8F8; }");//浅灰色
        chatList->setItemDelegate(new ChatMessageDelegate(this));




        QWidget *tab = new QWidget();//为tab部件创建一个垂直布局，所有添加到这个布局的控件都会在tab内垂直排列。
        QVBoxLayout *layout = new QVBoxLayout(tab);
        layout->addWidget(chatList);

        chatTabs->addTab(tab, userId);
        chatSessions.insert(userId, qMakePair(chatList, tab));
    }
    // 切换到对应标签页
    int index = chatTabs->indexOf(chatSessions[userId].second);
    chatTabs->setCurrentIndex(index);
}

//关闭标签
void MainWindow::onTabClosed(int index) {
    QWidget *tab = chatTabs->widget(index);
    QString userId = chatTabs->tabText(index);

    // 从映射中移除
    if (chatSessions.contains(userId)) {
        delete chatSessions[userId].first;
        delete chatSessions[userId].second;
        chatSessions.remove(userId);
    }
    chatTabs->removeTab(index);
}




void MainWindow::on_img_clicked()//点击了，发送表情
{


}

