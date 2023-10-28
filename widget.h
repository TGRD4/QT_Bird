#ifndef WIDGET_H
#define WIDGET_H

#include <QTimer>
#include <QWidget>
#include"flybird.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    // 鸟对象指针
    flyBird * bird;

    // 重写绘图事件
    void paintEvent(QPaintEvent *event);

    // 记录自动移动的位置
    QPoint Auto_Pos;

    // 自动移动定时器
    QTimer * timer;


private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
