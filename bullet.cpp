#include <iostream>
#include <QTimer>
#include "bullet.h"
#include "mainwindow.h"

extern MainWindow *main_window;

Bullet::Bullet(QWidget *parent) : QLabel(parent) {
    bullet_move_.vx_ = 10;
    bullet_move_.vy_ = 0;

    setFixedSize(BulletWidth, BulletHeight);

    damage_ = 2;
}

void Bullet::BulletMove() {
    QPoint bullet_pos = pos();
    int x = bullet_pos.x(), y = bullet_pos.y();
    
    // 检查子弹是否击中僵尸
    auto& zombie_q = main_window->zombie_queue();
    if(!zombie_q[line_].empty() && x >= zombie_q[line_].front()->pos().x() + 80) {  // + 80是为了视觉效果
        BulletHit(zombie_q[line_].front()); // front()是重载函数，可以是引用也可以是指针
        return;
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
    painter.drawPixmap(0, 0, this->width(), this->height(),QPixmap(":/image/bullet.png"));
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
    }

    Destory(this);
}
