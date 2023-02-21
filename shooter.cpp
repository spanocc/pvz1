#include "shooter.h"
#include "mainwindow.h"

extern MainWindow *main_window;


Shooter::Shooter(QWidget *parent, const QPoint& pos) 
    : Plant(parent, pos),
      produce_bullet_timer_(new QTimer(this)) {
    

}

void Shooter::BulletStart() {
    if(produce_bullet_switch_) return; // 已经在发射子弹了
    produce_bullet_switch_ = true;
    emit ProduceBullet(pos_, bullet_type_);  // 有僵尸出现，立马发射一个子弹，然后开启定时器，每5s射出一个子弹
    produce_bullet_timer_->start(2800); // 攻击间隔是3s，我设置成2.8s
}

void Shooter::BulletStop() {
    if(produce_bullet_switch_ == false) return; // 已经处于关闭状态
    produce_bullet_switch_ = false;
    produce_bullet_timer_->stop();
}

void Shooter::BulletInit() {
    // 建立产生子弹的时间间隔的信号函数
    connect(produce_bullet_timer_, &QTimer::timeout, this, [this]() {
        if(main_window->game_run_ == 0) return;
        emit ProduceBullet(pos_, bullet_type_); 
    });
    connect(this, &Shooter::ProduceBullet, main_window, &MainWindow::ProduceBullet);

    // 什么时候开始产生子弹
    connect(main_window->timer(), &QTimer::timeout, this, [this]() {
        // 检查这列僵尸队列中是否有僵尸在该豌豆前面
        for(const auto& it: main_window->zombie_queue()[line()]) {
            int zombie_pos = it->pos().x();
            int bullet_pos = pos_.x() + Graph::GraphBlockWidth - 50;
            // + 180是为了视觉效果，到僵尸中心才算击中 与bullet.cpp中的BulletMove函数中的处理相同
            if(bullet_pos <= zombie_pos + 180) {
                BulletStart();
                return;
            }
        }
        BulletStop();
    });
}

