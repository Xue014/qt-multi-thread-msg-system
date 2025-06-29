
#include "ChatMessageDelegate.h"
// 包含QPainter类，用于进行2D绘图操作
#include <QPainter>
// 包含QApplication类，它管理GUI应用程序的资源和控制流程
#include <QApplication>
// 包含QFontMetrics类，用于获取字体的度量信息，如字符的宽度、高度等
#include <QFontMetrics>
// 包含QPainterPath类，用于创建和操作绘图路径
#include <QPainterPath>
#include<QDebug>

// 构造函数，初始化ChatMessageDelegate对象，并将父对象指针传递给基类QStyledItemDelegate的构造函数
ChatMessageDelegate::ChatMessageDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

// 重写paint方法，用于自定义绘制列表项
void ChatMessageDelegate::paint(QPainter *painter,
                                //例如列表项的矩形区域、前景色、背景色、字体等。通过这个对象，可以获取到绘制列表项所需的基本样式信息，从而保证绘制的样式与视图的整体风格一致。
                                const QStyleOptionViewItem &option,  //根据当前列表项初始化的
                                 //QListWidget 中，每个列表项都对应数据模型中的一个索引，Qt 通过这个索引来定位要绘制的具体数据项。
                                //通过 index.data() 方法，可以从数据模型中获取列表项的各种数据，如显示文本、图标、自定义数据等
                                const QModelIndex &index) const
{
    // 保存当前绘图设备的状态，包括画笔、画刷、变换矩阵等，以便后续恢复
    painter->save();

    // 基本样式设置
    // 复制传入的option对象，避免修改原始对象
    QStyleOptionViewItem opt = option;
    // // 初始化样式选项，根据索引从模型中获取数据来设置选项的属性
    initStyleOption(&opt, index);
    // 设置绘图渲染提示，开启抗锯齿、文本抗锯齿和图像平滑变换，提高绘制质量
    painter->setRenderHints(QPainter::Antialiasing |
                            QPainter::TextAntialiasing |
                            QPainter::SmoothPixmapTransform);

    // 获取数据
    // 表示消息是否为发送方发出
    const bool isOutgoing = index.data(Qt::UserRole + 1).toBool();
    // 消息内容
    const QString message = index.data(Qt::DisplayRole).toString();
    // 消息时间戳
    const QString time = index.data(Qt::UserRole + 2).toDateTime()
                             .toString("hh:mm");


    // 计算布局区域
    //味着气泡宽度是列表项宽度的60%
    const int maxBubbleWidth = opt.rect.width() * BubbleWidthPercent;  //超过这个最大宽度就换行
    // qDebug()<<maxBubbleWidth;
    // QRect contentRect;
    // // 内容区域
    // if (opt.icon.isNull())
    // {
    //     contentRect = opt.rect.adjusted(2, 2, -2, -2);
    // }
    // else
    // {
    //     contentRect = opt.rect.adjusted(iconWidth + 2, 2, -2, -2); // 为图标留出空间

    // }
    const QRect contentRect =  opt.rect.adjusted(2, 2, -2, -2);





    //文本实际的宽度
    const QFontMetrics fm(opt.font);
    const int textMaxWidth = maxBubbleWidth - 2 * HorizontalPadding;// 文本的最大可用宽度（气泡宽度 - 左右内边距）

    const QRect textRect1 = fm.boundingRect(QRect(0, 0, maxBubbleWidth, INT_MAX),
                                            Qt::TextWrapAnywhere,
                                            message);
    // 气泡的实际宽度 = 文本宽度 + 左右内边距（不超过 maxBubbleWidth）


    int bubbleActualWidth = textRect1.width() + 2 * HorizontalPadding;
    if (!opt.icon.isNull()) {
        // 为图标留出空间，增加气泡宽度
        bubbleActualWidth += 50 + HorizontalPadding;
    }
    bubbleActualWidth = qMin(bubbleActualWidth, maxBubbleWidth);

    // 计算气泡位置
    //QRect::QRect(int x, int y, int width, int height);
    QRect bubbleRect;
    if(isOutgoing) {
        // 如果是发送方发出的消息，气泡从内容区域的右侧开始，宽度为最大气泡宽度，高度减去时间戳高度
        bubbleRect = QRect(contentRect.right() - bubbleActualWidth, //从0
                           contentRect.top(),
                           bubbleActualWidth,
                           contentRect.height() - TimeStampHeight);
    } else {
        // 如果是接收方的消息，气泡从内容区域的左侧开始，宽度为最大气泡宽度，高度减去时间戳高度
        bubbleRect = QRect(contentRect.left(),
                           contentRect.top(),
                           bubbleActualWidth,
                           contentRect.height() - TimeStampHeight);
    }

    // 绘制气泡
    // 创建一个绘图路径对象
    QPainterPath bubblePath;
    // 向路径中添加一个圆角矩形，圆角半径为BubbleRadius
    bubblePath.addRoundedRect(bubbleRect, BubbleRadius, BubbleRadius);

    // 设置画笔颜色，根据消息是发送还是接收使用不同的边框颜色
    painter->setPen(isOutgoing ? OutgoingBorderColor : IncomingBorderColor);
    // 设置画刷颜色，根据消息是发送还是接收使用不同的气泡背景颜色
    painter->setBrush(isOutgoing ? OutgoingBubbleColor : IncomingBubbleColor);
    // 绘制气泡路径
    painter->drawPath(bubblePath);






    // 绘制消息文本
    // 调整气泡矩形区域，向内缩小一定的水平和垂直填充距离，作为文本绘制区域
    QRect textRect = bubbleRect.adjusted(HorizontalPadding, VerticalPadding,
                                         -HorizontalPadding, -VerticalPadding);
    if (!opt.icon.isNull()) {
        // 调整文本区域，给图标留出位置
        textRect.adjust(50 + HorizontalPadding, 0, 0, 0);
    }
    // 设置画笔颜色为黑色
    painter->setPen(Qt::black);
    // 设置字体为样式选项中的字体
    painter->setFont(opt.font);


    if (!opt.icon.isNull()) {
        const QRect iconRect = QRect(bubbleRect.left() + HorizontalPadding, bubbleRect.top() + VerticalPadding, 25, 25);
        opt.icon.paint(painter, iconRect);
    }



    // 创建一个文本选项对象
    QTextOption textOption;
    // 设置文本换行模式为按单词换行
    textOption.setWrapMode(QTextOption::WordWrap);
    // 根据消息是发送还是接收设置文本对齐方式
    textOption.setAlignment(isOutgoing ? Qt::AlignRight : Qt::AlignLeft);
    // 在文本区域内绘制消息文本，使用设置好的文本选项
    painter->drawText(textRect, message, textOption);



    // 绘制时间戳
    // 计算时间戳的矩形区域，位于气泡下方，宽度为内容区域宽度，高度为时间戳高度
    QRect timeRect = QRect(contentRect.left(),
                           bubbleRect.bottom() + 2,
                           contentRect.width(),
                           TimeStampHeight);

    // 设置画笔颜色为时间戳颜色
    painter->setPen(TimeStampColor);
    // 设置字体为样式选项中的字体，但字号减小2
    painter->setFont(QFont(opt.font.family(), opt.font.pointSize() - 2));

    // 创建一个时间戳文本选项对象
    QTextOption timeOption;
    // 根据消息是发送还是接收设置时间戳文本对齐方式
    timeOption.setAlignment(isOutgoing ? Qt::AlignRight : Qt::AlignLeft);
    // 在时间戳区域内绘制时间戳文本，使用设置好的文本选项
    painter->drawText(timeRect, time, timeOption);

    // 恢复之前保存的绘图设备状态
    painter->restore();
}

// 重写sizeHint方法，用于返回列表项的建议尺寸
QSize ChatMessageDelegate::sizeHint(const QStyleOptionViewItem &option,
                                    const QModelIndex &index) const
{
    // 从模型索引中获取显示角色的数据，并转换为字符串，即消息内容
    const QString message = index.data(Qt::DisplayRole).toString();
    // 创建一个字体度量对象，用于获取字体的度量信息
    const QFontMetrics fm(option.font);

    // 计算文本所需空间
    // 计算气泡的最大宽度，为列表项宽度乘以BubbleWidthPercent比例，再减去两倍的水平填充距离
    const int maxBubbleWidth = option.rect.width() * BubbleWidthPercent
                               - 2 * HorizontalPadding;
    // 计算文本的边界矩形，考虑换行和最大宽度限制
    const QRect textRect = fm.boundingRect(QRect(0, 0, maxBubbleWidth, INT_MAX),
                                           Qt::TextWrapAnywhere,
                                           message);

    // 计算总高度
    // 计算气泡的高度，为文本高度加上两倍的垂直填充距离
    const int bubbleHeight = textRect.height() + 2 * VerticalPadding;
    // 计算列表项的总高度，为气泡高度加上时间戳高度和4像素的间隔
    int totalHeight = bubbleHeight + TimeStampHeight + 4;
    if (!option.icon.isNull()) {
        // 增加图标高度相关的额外空间
        totalHeight = qMax(totalHeight, textRect.height() + 50 + 2 * VerticalPadding + TimeStampHeight + 4);
    }

    // 返回建议尺寸，宽度为列表项宽度，高度为计算得到的总高度
    return QSize(option.rect.width(), totalHeight);
}

