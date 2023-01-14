#include "ordinaryzombie.h"

OrdinaryZombie::OrdinaryZombie(QWidget *parent) 
    : Zombie(parent) {

    zombie_type_ = ORDINARY;
    hit_point_ = 6;
    zombie_move_.vx_ = -1;
    zombie_move_.vy_ = 0;
    
    setFixedSize(OrdinaryZombieWidth, OrdinaryZombieHeight);
    DynamicImageInit();
    movie_->setSpeed(80);  // 设置gif播放速度
}