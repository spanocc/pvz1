#include <iostream>
#include "peashooter.h"
#include "mainwindow.h"

extern MainWindow *main_window;

PeaShooter::PeaShooter(QWidget *parent, const QPoint& pos)  
    : Shooter(parent, pos) {

    plant_type_ = PEASHOOTER;
    bullet_type_ = ORDINARY_BULLET;
    hit_point_ = 350;

    setFixedSize(QSize(PeaShooterWidth, PeaShooterHeight)); 
    DynamicImageInit();
    movie_->setSpeed(60);
    // 子弹初始化要在子类中使用，不能在Shooter的构造函数中来用，否则子类也需要声明BulletStart BulletStop ProduceBullet 这三个函数才能使用
    BulletInit();
/*
    // 建立产生子弹的时间间隔的信号函数
    connect(produce_bullet_timer_, &QTimer::timeout, this, [this]() {
        emit ProduceBullet(pos_); 
    });
    connect(this, &PeaShooter::ProduceBullet, main_window, &MainWindow::ProduceBullet);
*/       
}

/*
void PeaShooter::BulletStart() {
    if(produce_bullet_switch_) return; // 已经在发射子弹了
    produce_bullet_switch_ = true;
    emit ProduceBullet(pos_);  // 有僵尸出现，立马发射一个子弹，然后开启定时器，每5s射出一个子弹
    produce_bullet_timer_->start(2800); // 攻击间隔是3s，我设置成2.8s
}

void PeaShooter::BulletStop() {
    if(produce_bullet_switch_ == false) return; // 已经处于关闭状态
    produce_bullet_switch_ = false;
    produce_bullet_timer_->stop();
}
*/