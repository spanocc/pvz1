#include <iostream>
#include "zombie.h"
#include "mainwindow.h"

extern MainWindow *main_window;

const char *zombie_name[] = {
/* 0  */ "ordinaryzombie"
/* 1  */ 
/* 2  */ 
};

Zombie::Zombie(QWidget *parent) 
    : QLabel(parent) {

}

void Zombie::DynamicImageInit() {
    assert(init_movie_ == nullptr);
    std::string movie_path = std::string(":/image/") + zombie_name[zombie_type_] + ".gif";   
    init_movie_ = new QMovie(movie_path.c_str());
    init_movie_->setScaledSize(this->size());
    // movie_->setSpeed(100);  // 设置播放速度 (每个gif速度不一样，在类内单独设置)


    assert(attack_movie_ == nullptr);
    movie_path = std::string(":/image/") + zombie_name[zombie_type_] + "attack.gif";   
    attack_movie_ = new QMovie(movie_path.c_str());
    attack_movie_->setScaledSize(this->size());


    // 设置成僵尸的初始状态
    this->setMovie(init_movie_);
    init_movie_->start();
}

void Zombie::ZombieMove() {
    QPoint zombie_pos = pos();
    int x = zombie_pos.x(), y = zombie_pos.y();

    if(x <= 0) {
        std::cout<<"game over!\n";
        emit Destroy(this);
        return;
    }
    // 看僵尸所在格子里有没有植物            +200是为了使列数与视觉效果的列数对齐，这个数字根据实际效果来调整
    column_ = (pos().x() - Graph::InitGraphX + 200) / Graph::GraphBlockWidth;        // std::cout<<column_<<"\n";

    if(column_ >= 0 && column_ < Graph::ColumnNum) {
        Plant *plant = main_window->graph()->graph()[line_][column_]->plant();
        if(plant) {
            ZombieAttack(plant);
            return;
        } else if(state_ == ZOMBIE_ATTACK) {
            state_ = ZOMBIE_INIT;
            this->setMovie(init_movie_);
            init_movie_->start();
        }
    }

    move(x + zombie_move_.vx_, y + zombie_move_.vy_); 
}

void Zombie::KillZombie() {
    emit Destroy(this);
}

void Zombie::ZombieAttack(Plant *plant) {
    int& hp = plant->hp();
    if(damage_ >= hp) {
        plant->KillPlant();
    } else {
        hp -= damage_;
    }

    if(state_ == ZOMBIE_INIT) {
        state_ = ZOMBIE_ATTACK;
        this->setMovie(attack_movie_);
        attack_movie_->start();
    }
}