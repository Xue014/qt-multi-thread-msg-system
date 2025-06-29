QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chatmessagedelegate.cpp \
    main.cpp \
    mainwindow.cpp \
    mylistwidgetitem.cpp \
    oneuser.cpp \
    uselogin.cpp

HEADERS += \
    chatmessagedelegate.h \
    mainwindow.h \
    mylistwidgetitem.h \
    oneuser.h \
    uselogin.h

FORMS += \
    mainwindow.ui \
    uselogin.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
