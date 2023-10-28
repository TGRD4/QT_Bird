#ifndef FLYBIRD_H
#define FLYBIRD_H

#include <QWidget>
#include<QPixmap>
#include <QTimer>
#include<QPoint>
#include <QMenu>
#include<QImage>

class flyBird : public QWidget
{
    Q_OBJECT
public:
    explicit flyBird(QWidget *parent = nullptr);

    // 鸟显示的图片
    QPixmap Bird_Pix;
    // 提前加载8张图片就不会一直报警告

    // 使用QImage对图片做像素级处理（镜像图片 ）
    QImage * image;

    int min = 1;    // 最小值图片下标
    int max = 8;    // 最大值图片下标

    // 定时器
    QTimer * timer;

    // 执行动画函数
    void running();

    // 记录分量坐标
    QPoint Pos;

    // 重写鼠标按下事件
    void mousePressEvent(QMouseEvent *event);

    // 重写鼠标移动事件
    void mouseMoveEvent(QMouseEvent *event);

    // 鼠标释放事件
    void mouseReleaseEvent(QMouseEvent *event);

    // 添加鼠标按下的状态
    bool mouseDown = false;

    // 右键菜单，实现退出
    QMenu * menu;

    // 什么时候镜像的标志位
    bool isMirrored = false;

    // 到达顶部和底部的标志位
    bool isTop = false;

signals:
    // 自定义信号    代表正在动画切图
    void changePix();

    // 拖拽后主场景应该移动的位置
    void moving(QPoint point);

};

#endif // FLYBIRD_H
