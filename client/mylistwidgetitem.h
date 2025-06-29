#ifndef MYLISTWIDGETITEM_H
#define MYLISTWIDGETITEM_H

// 包含必要的头文件
#include <QWidget>
#include <QMouseEvent>
#include <QIcon>
#include <QImage>
#include <QPixmap>
#include <QLabel>


// 自定义列表项类，继承自 QWidget
class MyListWidgetItem : public QWidget
{
    // 声明 Qt 的元对象系统支持
    Q_OBJECT

public:
    // 构造函数，接收图像和文本
    MyListWidgetItem(QIcon icon, QString string);

    // 析构函数
    ~MyListWidgetItem();

    // 设置和获取索引的函数
    void setIndex(int ind);
    int getIndex();

    // 重写鼠标按下事件处理函数
    void mousePressEvent(QMouseEvent *event);
    void setData(int role, const QVariant &value);

signals:
    // 声明点击信号，携带被点击项的索引
    void listItemClicked(int);

private:

    // 存储列表项的索引
    int index;
};

#endif
