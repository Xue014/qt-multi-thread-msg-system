/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QListWidget *useall;
    QTextEdit *message;
    QPushButton *sendmes;
    QTabWidget *chatTabs;
    QWidget *widget;
    QWidget *tab_2;
    QLabel *choosname;
    QTextBrowser *textBrowser;
    QWidget *clear;
    QHBoxLayout *horizontalLayout;
    QPushButton *img;
    QPushButton *sendfile;
    QSpacerItem *horizontalSpacer;
    QPushButton *yy;
    QPushButton *sp;
    QTextEdit *cebianlian;
    QPushButton *chatbtn;
    QPushButton *friend_2;
    QLabel *CHAT;
    QMenuBar *menubar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1152, 817);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        useall = new QListWidget(centralwidget);
        useall->setObjectName(QString::fromUtf8("useall"));
        useall->setGeometry(QRect(55, 10, 211, 781));
        message = new QTextEdit(centralwidget);
        message->setObjectName(QString::fromUtf8("message"));
        message->setGeometry(QRect(270, 650, 881, 141));
        sendmes = new QPushButton(centralwidget);
        sendmes->setObjectName(QString::fromUtf8("sendmes"));
        sendmes->setGeometry(QRect(1050, 750, 91, 31));
        chatTabs = new QTabWidget(centralwidget);
        chatTabs->setObjectName(QString::fromUtf8("chatTabs"));
        chatTabs->setGeometry(QRect(270, 50, 911, 561));
        chatTabs->setTabPosition(QTabWidget::East);
        chatTabs->setTabShape(QTabWidget::Rounded);
        chatTabs->setUsesScrollButtons(true);
        chatTabs->setTabsClosable(true);
        widget = new QWidget();
        widget->setObjectName(QString::fromUtf8("widget"));
        chatTabs->addTab(widget, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        chatTabs->addTab(tab_2, QString());
        choosname = new QLabel(centralwidget);
        choosname->setObjectName(QString::fromUtf8("choosname"));
        choosname->setGeometry(QRect(280, 0, 831, 41));
        textBrowser = new QTextBrowser(centralwidget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(270, 608, 881, 41));
        clear = new QWidget(centralwidget);
        clear->setObjectName(QString::fromUtf8("clear"));
        clear->setGeometry(QRect(280, 600, 871, 61));
        horizontalLayout = new QHBoxLayout(clear);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        img = new QPushButton(clear);
        img->setObjectName(QString::fromUtf8("img"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/image/img.png"), QSize(), QIcon::Normal, QIcon::Off);
        img->setIcon(icon);
        img->setIconSize(QSize(30, 30));

        horizontalLayout->addWidget(img);

        sendfile = new QPushButton(clear);
        sendfile->setObjectName(QString::fromUtf8("sendfile"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/image/sendm.png"), QSize(), QIcon::Normal, QIcon::Off);
        sendfile->setIcon(icon1);
        sendfile->setIconSize(QSize(30, 30));

        horizontalLayout->addWidget(sendfile);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        yy = new QPushButton(clear);
        yy->setObjectName(QString::fromUtf8("yy"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/image/yyth.png"), QSize(), QIcon::Normal, QIcon::Off);
        yy->setIcon(icon2);
        yy->setIconSize(QSize(30, 30));

        horizontalLayout->addWidget(yy);

        sp = new QPushButton(clear);
        sp->setObjectName(QString::fromUtf8("sp"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/image/sptt.png"), QSize(), QIcon::Normal, QIcon::Off);
        sp->setIcon(icon3);
        sp->setIconSize(QSize(30, 30));

        horizontalLayout->addWidget(sp);

        cebianlian = new QTextEdit(centralwidget);
        cebianlian->setObjectName(QString::fromUtf8("cebianlian"));
        cebianlian->setGeometry(QRect(0, 10, 61, 781));
        chatbtn = new QPushButton(centralwidget);
        chatbtn->setObjectName(QString::fromUtf8("chatbtn"));
        chatbtn->setGeometry(QRect(10, 60, 41, 41));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/image/chat1.png"), QSize(), QIcon::Normal, QIcon::Off);
        chatbtn->setIcon(icon4);
        friend_2 = new QPushButton(centralwidget);
        friend_2->setObjectName(QString::fromUtf8("friend_2"));
        friend_2->setGeometry(QRect(10, 110, 41, 41));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/image/friend.png"), QSize(), QIcon::Normal, QIcon::Off);
        friend_2->setIcon(icon5);
        CHAT = new QLabel(centralwidget);
        CHAT->setObjectName(QString::fromUtf8("CHAT"));
        CHAT->setGeometry(QRect(10, 20, 71, 21));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1152, 25));
        MainWindow->setMenuBar(menubar);

        retranslateUi(MainWindow);

        chatTabs->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        sendmes->setText(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201\346\266\210\346\201\257", nullptr));
        chatTabs->setTabText(chatTabs->indexOf(widget), QCoreApplication::translate("MainWindow", "Tab 1", nullptr));
        chatTabs->setTabText(chatTabs->indexOf(tab_2), QCoreApplication::translate("MainWindow", "Tab 2", nullptr));
        choosname->setText(QString());
        img->setText(QString());
        sendfile->setText(QString());
        yy->setText(QString());
        sp->setText(QString());
        chatbtn->setText(QString());
        friend_2->setText(QString());
        CHAT->setText(QCoreApplication::translate("MainWindow", "CHAT", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
