/********************************************************************************
** Form generated from reading UI file 'uselogin.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USELOGIN_H
#define UI_USELOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UseLogin
{
public:
    QWidget *centralwidget;
    QLineEdit *name;
    QLineEdit *password;
    QLabel *name_2;
    QLabel *password_2;
    QPushButton *login;
    QPushButton *zhuce;
    QLabel *welcom;

    void setupUi(QMainWindow *UseLogin)
    {
        if (UseLogin->objectName().isEmpty())
            UseLogin->setObjectName(QString::fromUtf8("UseLogin"));
        UseLogin->resize(388, 558);
        centralwidget = new QWidget(UseLogin);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        name = new QLineEdit(centralwidget);
        name->setObjectName(QString::fromUtf8("name"));
        name->setGeometry(QRect(130, 200, 200, 40));
        password = new QLineEdit(centralwidget);
        password->setObjectName(QString::fromUtf8("password"));
        password->setGeometry(QRect(130, 260, 200, 40));
        name_2 = new QLabel(centralwidget);
        name_2->setObjectName(QString::fromUtf8("name_2"));
        name_2->setGeometry(QRect(50, 210, 69, 21));
        password_2 = new QLabel(centralwidget);
        password_2->setObjectName(QString::fromUtf8("password_2"));
        password_2->setGeometry(QRect(50, 280, 69, 19));
        login = new QPushButton(centralwidget);
        login->setObjectName(QString::fromUtf8("login"));
        login->setGeometry(QRect(50, 350, 281, 41));
        zhuce = new QPushButton(centralwidget);
        zhuce->setObjectName(QString::fromUtf8("zhuce"));
        zhuce->setGeometry(QRect(50, 410, 281, 41));
        welcom = new QLabel(centralwidget);
        welcom->setObjectName(QString::fromUtf8("welcom"));
        welcom->setGeometry(QRect(70, 40, 241, 91));
        UseLogin->setCentralWidget(centralwidget);

        retranslateUi(UseLogin);

        QMetaObject::connectSlotsByName(UseLogin);
    } // setupUi

    void retranslateUi(QMainWindow *UseLogin)
    {
        UseLogin->setWindowTitle(QCoreApplication::translate("UseLogin", "MainWindow", nullptr));
        name_2->setText(QCoreApplication::translate("UseLogin", "\347\224\250\346\210\267\345\220\215\357\274\232", nullptr));
        password_2->setText(QCoreApplication::translate("UseLogin", "\345\257\206\347\240\201\357\274\232", nullptr));
        login->setText(QCoreApplication::translate("UseLogin", "\347\231\273\345\275\225", nullptr));
        zhuce->setText(QCoreApplication::translate("UseLogin", "\346\263\250\345\206\214", nullptr));
        welcom->setText(QCoreApplication::translate("UseLogin", "welcome to", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UseLogin: public Ui_UseLogin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USELOGIN_H
