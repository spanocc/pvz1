#include "sunflower.h"
#include "mainwindow.h"

extern MainWindow *main_window; 

SunFlower::SunFlower(QWidget *parent, const QPoint& pos) 
    : Plant(parent, pos),
      produce_sun_timer_(new QTimer(this)) {
    
    // image_num_ = 18;
    plant_type_ = SUNFLOWER;
    hit_point_ = 350;

    setFixedSize(QSize(SunFlowerWidth, SunFlowerHeight));    
    // 设置向日葵的动态效果
    DynamicImageInit();
    movie_->setSpeed(100);  // 设置gif播放速度
    // 建立产生阳光的信号函数
    connect(produce_sun_timer_, &QTimer::timeout, this, [this]() {
      if(main_window->game_run_ == 0) return;
        emit ProduceSun(pos_); // 阳光的位置应该是相对于主窗口的，而pos函数调用的位置是相对于该graph_block的
    });
    void (MainWindow::*produce_sunflower_sun)(const QPoint&) = &MainWindow::ProduceSun; // 指向含有QPoint参数的ProduceSun函数的指针
    connect(this, &SunFlower::ProduceSun, main_window, produce_sunflower_sun);
    produce_sun_timer_->start(25000);

}
