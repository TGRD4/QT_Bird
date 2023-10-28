#include "widget.h"
#include "ui_widget.h"
#include "flybird.h"
#include<QGuiApplication>
#include <QScreen>
#include <QImage>
#include <QDebug>
#include<QPainter>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 设置图标
    this->setWindowIcon(QIcon(":/bird/birdIcon.ico"));

    // 创建鸟对象
    this->bird = new flyBird;

    // 将鸟对象显示到窗口中
    this->bird->setParent(this);

    // 设置窗口尺寸
    this->setFixedSize(this->bird->width(),this->bird->height());

    // 启动阿呆
    this->bird->running();

    // 监听阿呆切图的信号
    connect(this->bird,&flyBird::changePix,[=]() {
        update();   // 手动调用绘图事件
    });

    // 监听阿呆拖拽移动的信号
    connect(this->bird,&flyBird::moving,[=](QPoint point) {
        this->move(point);

        // 鼠标移动之后，更新当前窗口位置
        Auto_Pos = point;
    });

    // 创建定时器对象
    this->timer = new QTimer(this);

    // 启动定时器    坐标自动移动30ms/move
    this->timer->start(15);

    //获取主屏分辨率
    QRect desk = QGuiApplication::primaryScreen()->geometry();

    // 监听定时器
    connect(timer,&QTimer::timeout,[=]() {
        // 若鼠标没有按下，才向前自动移动
        if(this->bird->mouseDown != true) {
            if(this->bird->isMirrored==false) {
                this->Auto_Pos.setX(this->Auto_Pos.x()+5);  // 向右飞 5 像素
            }
            if(this->bird->isMirrored==true) {
                this->Auto_Pos.setX(this->Auto_Pos.x()-5);  // 向左飞 5 像素

            }
            if(this->bird->isTop==false) {

                this->Auto_Pos.setY(this->Auto_Pos.y()-2);
            }
            if(this->bird->isTop==true) {

                this->Auto_Pos.setY(this->Auto_Pos.y()+2);
            }

        }

        // 到达屏幕右侧后从转向飞回
        if(this->Auto_Pos.x() >= desk.width()-this->bird->Bird_Pix.width() ) {
            this->bird->isMirrored=true;
        }
        // 到达屏幕左侧后从转向飞回
        if(this->Auto_Pos.x() <= 0) {
             this->bird->isMirrored=false;
        }
        if(this->Auto_Pos.y()<=0) {
             this->bird->isTop=true;
        }
        if(this->Auto_Pos.y() >=desk.height()-this->bird->Bird_Pix.height()) {
             this->bird->isTop=false;
        }


        // 窗口同步移动
        this->move(this->Auto_Pos);

    });

    // 去掉标题栏
    this->setWindowFlags(Qt::FramelessWindowHint);

    // 设置透明窗体       120号属性
    this->setAttribute(Qt::WA_TranslucentBackground);

    // 设置窗口顶层
    this->setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint);

    // 设置起始 Y 位置
    this->Auto_Pos.setY(desk.height()*0.4 - this->bird->height());


}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,this->bird->Bird_Pix);
}

