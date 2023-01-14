#include <iostream>
#include "zombie.h"

const char *zombie_name[] = {
/* 0  */ "ordinaryzombie"
/* 1  */ 
/* 2  */ 
};


Zombie::Zombie(QWidget *parent) 
    : QLabel(parent) {

}

void Zombie::DynamicImageInit() {
    assert(movie_ == nullptr);
    std::string movie_path = std::string(":/image/") + zombie_name[zombie_type_] + ".gif";   
    movie_ = new QMovie(movie_path.c_str());
    movie_->setScaledSize(this->size());
    // movie_->setSpeed(100);  // 设置播放速度 (每个gif速度不一样，在类内单独设置)
    this->setMovie(movie_);
    movie_->start();
}

void Zombie::ZombieMove() {
    QPoint zombie_pos = pos();
    int x = zombie_pos.x(), y = zombie_pos.y();

    if(x <= 0) {
        std::cout<<"game over!\n";
    }

    move(x + zombie_move_.vx_, y + zombie_move_.vy_); 
}

void Zombie::KillZombie() {
    emit Destroy(this);
}