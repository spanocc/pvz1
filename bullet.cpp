#include <iostream>
#include <string>
#include <QTimer>
#include "bullet.h"
#include "mainwindow.h"

extern MainWindow *main_window;

Bullet::Bullet(QWidget *parent, BulletType bullet_type) : QLabel(parent), bullet_type_(bullet_type) {
    bullet_move_.vx_ = 20;
    bullet_move_.vy_ = 0;

    setFixedSize(BulletWidth, BulletHeight);

    // damage_ = 2;
    damage_ = 20; // 普通子弹的攻击力
}

void Bullet::BulletMove() {
    // 说明此时正在播放子弹破碎的gif,不移动
    if(state_ == BULLET_BREAK) return;

    QPoint bullet_pos = pos();
    int x = bullet_pos.x(), y = bullet_pos.y();
    
    // 检查子弹是否击中僵尸
    auto& zombie_q = main_window->zombie_queue();
    for(const auto& it: zombie_q[line_]) {
        // + 180是为了视觉效果，到僵尸中心才算击中                    子弹和僵尸相撞的误差 < 25 (子弹一帧移动的距离是20, 僵尸一帧移动的距离是1)
        if(x >= it->pos().x() + 180 && x - (it->pos().x() + 180) <= 25 ) {
            BulletHit(it); 
            return;
        }
    }
    // 子弹超出屏幕要销毁
    if(x > MainWindow::MainWindowWidth) {
        emit Destory(this);
        return;
    }
    move(x + bullet_move_.vx_, y + bullet_move_.vy_);
}

void Bullet::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    std::string image_path; 
    if(state_ == BULLET_BREAK) { // 显示子弹破碎
        setFixedSize(100, 100);
        if(bullet_type_ == ORDINARY_BULLET) image_path = ":/image/peabullethit.gif";
        else if(bullet_type_ == SNOW_BULLET) image_path = ":/image/snowbullethit.png";
        painter.drawPixmap(0, 0, this->width(), this->height(), QPixmap(image_path.c_str()));
    } else {
        if(bullet_type_ == ORDINARY_BULLET) image_path = ":/image/bullet.png";
        else if(bullet_type_ == SNOW_BULLET) image_path = ":/image/snowbullet.png";
        painter.drawPixmap(0, 0, this->width(), this->height(), QPixmap(image_path.c_str()));
    }
}

Bullet::~Bullet() {
    std::cout<<"destroy a bullet\n";
}

void Bullet::BulletHit(Zombie *zombie) {
    int &hp = zombie->hp();
    if(hp <= damage_) {
        zombie->KillZombie();
    } else {
        hp -= damage_;
        zombie->ZombieHit(); // 僵尸被攻击特效
        if(bullet_type_ == SNOW_BULLET) zombie->ZombieSlowDown(); 
    }

    state_ = BULLET_BREAK;

    // 放0.5秒子弹破碎的gif再销毁
    QTimer *destroy_timer = new QTimer(this);
    connect(destroy_timer, &QTimer::timeout, this, [this]() {
        emit Destory(this);
    });
    destroy_timer->start(500);
   
}
