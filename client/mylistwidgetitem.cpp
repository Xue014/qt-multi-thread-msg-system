#include "mylistwidgetitem.h"

#include <QHBoxLayout>
MyListWidgetItem::MyListWidgetItem(QIcon icon, QString string)
{
    // 创建主布局
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(5, 5, 5, 5);
    mainLayout->setSpacing(10);

    // 创建图标标签
    QLabel *iconLabel = new QLabel(this);
    iconLabel->setPixmap(icon.pixmap(32, 32));
    iconLabel->setFixedSize(32, 32);
    mainLayout->addWidget(iconLabel);

    // 创建文本标签
    QLabel *textLabel = new QLabel(string, this);
    textLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    textLabel->setWordWrap(true);
    mainLayout->addWidget(textLabel, 1); // 让文本标签占据剩余空间


}
void MyListWidgetItem::setIndex(int ind)
{
    // 保存列表项的索引值，用于识别是哪个项被点击
    this->index = ind;
}

int MyListWidgetItem::getIndex()
{
    // 返回保存的索引值
    return index;
}
void MyListWidgetItem::mousePressEvent(QMouseEvent *event)
{
    // 检查是否为鼠标左键点击
    if (event->button() == Qt::LeftButton)
    {
        // 发出带索引参数的信号，通知主界面哪个项被点击了
        emit this->listItemClicked(index);
    }
}
void MyListWidgetItem::setData(int role, const QVariant &value)
{
    // 怎么写 ？，参考ListWidgetItem里面的setData
    Q_UNUSED(role);
    Q_UNUSED(value);
}
MyListWidgetItem::~MyListWidgetItem()
{

}
