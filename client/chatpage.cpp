#include "chatpage.h"

ChatPage::ChatPage(const QString &friendId, QWidget *parent)
    : QWidget(parent), m_friendId(friendId) {
    QVBoxLayout *layout = new QVBoxLayout(this);

    // 聊天记录显示区域（只读）
    m_chatHistory = new QTextEdit;
    m_chatHistory->setReadOnly(true);
    layout->addWidget(m_chatHistory);

    // 输入框和发送按钮
    QHBoxLayout *inputLayout = new QHBoxLayout;
    m_inputEdit = new QLineEdit;
    m_sendButton = new QPushButton("发送");
    inputLayout->addWidget(m_inputEdit);
    inputLayout->addWidget(m_sendButton);
    layout->addLayout(inputLayout);

    connect(m_sendButton, &QPushButton::clicked, this, &ChatPage::onSendButtonClicked);
}

QString ChatPage::getFriendId() const {
    return m_friendId;
}

void ChatPage::appendMessage(const QString &content) {
    QString time = QDateTime::currentDateTime().toString("HH:mm:ss");
    m_chatHistory->append(QString("[%1] 我: %2").arg(time, content)); // 发送方固定为当前用户，实际需区分
}

void ChatPage::onSendButtonClicked() {
    QString content = m_inputEdit->text().trimmed();
    if (!content.isEmpty()) {
        emit messageSent(content); // 发送消息内容（好友 ID 需从页面自身获取）
        appendMessage(content);
        m_inputEdit->clear();
    }
}
