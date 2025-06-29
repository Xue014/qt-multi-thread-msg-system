// ChatMessageDelegate.h
#include <QStyledItemDelegate>

class ChatMessageDelegate : public QStyledItemDelegate {
public:
    ChatMessageDelegate(QObject *parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};
