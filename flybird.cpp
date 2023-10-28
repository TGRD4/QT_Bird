#include "flybird.h"

#include <QMouseEvent>

flyBird::flyBird(QWidget *parent)
    : QWidget{parent}
{

    // 使用QImage对图片做像素级处理（镜像图片 ）
    image = new QImage();

    // 提前加载所有图片资源
    for(int i=0;i<this->max;i++) {
        QString str = QString(":/bird/bird%1").arg(i+1);
        this->Bird_Pix.load(str);
    }

    // 设置鸟的尺寸
    this->setFixedSize(this->Bird_Pix.width(),this->Bird_Pix.height());

    // 创建定时器对象
    this->timer = new QTimer(this);

    // 监听定时器信号
    connect(timer,&QTimer::timeout,[=]() {
\

        QString str = QString(":/bird/bird%1").arg(this->min++);
        this->Bird_Pix.load(str);

        // 将Pixmap绘图设备转成Image进行镜像处理后再赋给Pixmap
        if(isMirrored==true) {
            *image = Bird_Pix.toImage();
            *image = image->mirrored(true,false);
            Bird_Pix = QPixmap::fromImage(*image);
        }

        if(this->min > this->max) {         // 重置图片
            this->min = 1;
        }
        // 抛出自定义信号
        emit changePix();

    });

    // 创建菜单
    this->menu = new QMenu();

    // 连接信号槽
    connect(this->menu->addAction("退出"),&QAction::triggered,[=]() {
        exit(0);
    });


}

void flyBird::running()
{
    //  启动定时器
    this->timer->start(50);
}

void flyBird::mousePressEvent(QMouseEvent *event)
{
    // 鼠标按下时记录分量                获取当前窗口左上角的坐标
    this->Pos = event->globalPos() - ((QWidget*)this->parent())->frameGeometry().topLeft();

    // 鼠标按下状态为真
    mouseDown = true;

    // 如果是鼠标右键，则弹出菜单
    if(event->button() == Qt::RightButton) {
        // 弹出菜单到鼠标当前位置
        this->menu->popup(QCursor::pos());
    }

    // 若果菜单是通过别的方式消失的，阿呆应该继续往前飞
    connect(this->menu,&QMenu::aboutToHide,[=]() {
        this->mouseDown = false;
    });
}

void flyBird::mouseMoveEvent(QMouseEvent *event)
{
    // 在移动过程中       反向获取到       窗口最终移动的位置
    emit  this->moving(event->globalPos() - this->Pos);

}

void flyBird::mouseReleaseEvent(QMouseEvent *event)
{
    // 鼠标按下状态为假
    mouseDown = false;
}
