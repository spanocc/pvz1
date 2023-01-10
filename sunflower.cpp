#include "sunflower.h"
#include "mainwindow.h"

extern MainWindow *main_window; 

SunFlower::SunFlower(QWidget *parent) 
    : Plant(parent),
      produce_sun_timer_(new QTimer(this)) {
    
    image_num_ = 18;
    plant_type_ = SUNFLOWER;

    setFixedSize(QSize(SunFlowerWidth, SunFlowerHeight));    
    // 设置向日葵的动态效果
    DynamicImageInit();
    // 建立产生阳光的信号函数
    connect(produce_sun_timer_, &QTimer::timeout, this, [this]() {
        emit ProduceSun(pos_); // 阳光的位置应该是相对于主窗口的，而pos函数调用的位置是相对于该graph_block的
    });
    void (MainWindow::*produce_sunflower_sun)(const QPoint&) = &MainWindow::ProduceSun; // 指向含有QPoint参数的ProduceSun函数的指针
    connect(this, &SunFlower::ProduceSun, main_window, produce_sunflower_sun);

    produce_sun_timer_->start(15000);
}
