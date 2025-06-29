// ChatMessageDelegate.cpp
#include "chatmessage.h"
#include<QPainter>
#include<QTextOption>

ChatMessageDelegate::ChatMessageDelegate(QObject *parent) : QStyledItemDelegate(parent) {}

void ChatMessageDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    // 获取数据：isSelf 表示是否是自己的消息，message 是内容
    bool isSelf = index.data(Qt::UserRole + 1).toBool();
    QString message = index.data(Qt::DisplayRole).toString();

    painter->save();

    // 设置背景和边框
    QRect bubbleRect = option.rect.adjusted(5, 5, -5, -5);
    QColor bubbleColor = isSelf ? QColor("#DCF8C6") : QColor("#FFFFFF");
    painter->setBrush(bubbleColor);
    painter->setPen(QPen(QColor(isSelf? "#B2D8B2" : "#E0E0E0"), 1));
    painter->drawRoundedRect(bubbleRect, 8, 8);

    // 设置文本对齐和位置
    QTextOption textOption;
    textOption.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
    textOption.setAlignment(isSelf ? Qt::AlignRight : Qt::AlignLeft);

    QRect textRect = bubbleRect.adjusted(8, 4, -8, -4);
    painter->drawText(textRect, message, textOption);

    painter->restore();
}

QSize ChatMessageDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    // 动态计算消息气泡的大小
    QString message = index.data(Qt::DisplayRole).toString();
    QFontMetrics fm(option.font);
    int textWidth = fm.horizontalAdvance(message) + 20; // 加上边距
    int textHeight = fm.boundingRect(QRect(0, 0, 300, 0), Qt::TextWordWrap, message).height() + 16;

    return QSize(qMin(textWidth, 300), textHeight); // 限制最大宽度
}
