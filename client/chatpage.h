#ifndef CHATPAGE_H
#define CHATPAGE_H

#include <QWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

class ChatPage : public QWidget {
    Q_OBJECT
public:
    explicit ChatPage(const QString &friendId, QWidget *parent = nullptr);
    QString getFriendId() const; // 获取当前聊天的好友 ID
    void appendMessage(const QString &content); // 向聊天记录添加消息

signals:
    void messageSent(const QString &content); // 发送消息的信号

private slots:
    void onSendButtonClicked(); // 发送按钮点击处理

private:
    QString m_friendId; // 当前聊天的好友 ID
    QTextEdit *m_chatHistory; // 聊天记录显示区域
    QLineEdit *m_inputEdit; // 消息输入框
    QPushButton *m_sendButton; // 发送按钮
};

#endif // CHATPAGE_H
