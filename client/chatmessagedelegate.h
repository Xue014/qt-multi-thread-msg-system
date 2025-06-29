// ChatMessageDelegate.h
#ifndef CHATMESSAGEDELEGATE_H
#define CHATMESSAGEDELEGATE_H

#include <QStyledItemDelegate>
#include <QDateTime>

class ChatMessageDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    // 定义数据角色
    enum DataRoles {
        IsOutgoingRole = Qt::UserRole + 1, // 消息方向
        TimestampRole = Qt::UserRole + 2  // 时间戳
    };

    explicit ChatMessageDelegate(QObject *parent = nullptr);

    // 必须重写的函数
    void paint(QPainter *painter,
               const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;

    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const override;

private:
    // 样式参数
    const int BubbleRadius = 8;          // 气泡圆角半径
    const int HorizontalPadding = 12;    // 水平内边距
    const int VerticalPadding = 8;       // 垂直内边距
    const int TimeStampHeight = 20;      // 时间戳区域高度
    const qreal BubbleWidthPercent = 0.6;// 气泡最大宽度百分比

    const int iconWidth = 32;//图标大小

    // 颜色定义
    const QColor OutgoingBubbleColor = QColor(220, 248, 198); // 发送气泡颜色
    const QColor IncomingBubbleColor = Qt::white;             // 接收气泡颜色
    const QColor OutgoingBorderColor = QColor(178, 216, 178); // 发送边框颜色
    const QColor IncomingBorderColor = QColor(224, 224, 224); // 接收边框颜色
    const QColor TimeStampColor = Qt::gray;                   // 时间戳颜色
};

#endif // CHATMESSAGEDELEGATE_H
