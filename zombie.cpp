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
    
    hit_timer_ = new QTimer(this);
    connect(hit_timer_, &QTimer::timeout, this, [this](){
        hit_flag_ = false;
        hit_timer_->stop();
    });
}

void Zombie::DynamicImageInit() {
    // init状态
    assert(init_movie_ == nullptr);
    std::string movie_path = std::string(":/image/") + zombie_name[zombie_type_] + ".gif";   
    init_movie_ = new QMovie(movie_path.c_str());
    init_movie_->setScaledSize(this->size());
    // movie_->setSpeed(100);  // 设置播放速度 (每个gif速度不一样，在类内单独设置)

    // 把movie分解成一帧一帧的图片，然后对图片设置，仍然用类似sun的方式更换图像，这样可以对图像进行操作
    init_movie_->setCacheMode(QMovie::CacheAll);
    init_image_num_ = init_movie_->frameCount();
    init_dynamic_timer_ = new QTimer(this);
    connect(init_dynamic_timer_, &QTimer::timeout, this, [&]() {
        init_current_image_ = (init_current_image_ + 1) % init_image_num_;
        update(); // 更新图像
    });
    // init_dynamic_timer_->start(160);

    // attack状态
    assert(attack_movie_ == nullptr);
    movie_path = std::string(":/image/") + zombie_name[zombie_type_] + "attack.gif";   
    attack_movie_ = new QMovie(movie_path.c_str());
    attack_movie_->setScaledSize(this->size());

    attack_movie_->setCacheMode(QMovie::CacheAll);
    attack_image_num_ = attack_movie_->frameCount();
    attack_dynamic_timer_ = new QTimer(this);
    connect(attack_dynamic_timer_, &QTimer::timeout, this, [&]() {
        attack_current_image_ = (attack_current_image_ + 1) % attack_image_num_;
        update(); // 更新图像
    });
    // attack_dynamic_timer_->start(160);

    // 僵尸受到攻击时



    // 设置成僵尸的初始状态
    // this->setMovie(init_movie_);
    // init_movie_->start();
    init_dynamic_timer_->start(160);
    
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
            // this->setMovie(init_movie_);
            // init_movie_->start();
            attack_movie_->stop();
            init_current_image_ = 0;
            init_dynamic_timer_->start(160);
            update(); // 更新图像
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
        // this->setMovie(attack_movie_);
        // attack_movie_->start();
        init_movie_->stop();
        attack_current_image_ = 0;
        attack_dynamic_timer_->start(160);
        update(); // 更新图像
    }
}
// 僵尸被攻击后的特效
void Zombie::ZombieHit() {
    hit_flag_ = true;
    hit_timer_->start(50);
    update();
}

void Zombie::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    QPixmap pixmap;
    if(state_ == ZOMBIE_INIT) {
        init_movie_->jumpToFrame(init_current_image_);
        pixmap = init_movie_->currentPixmap();
    }
    else if(state_ == ZOMBIE_ATTACK) {
        attack_movie_->jumpToFrame(attack_current_image_);
        pixmap = attack_movie_->currentPixmap();    
    }
    if(hit_flag_) painter.setOpacity(0.5);
    painter.drawPixmap(0, 0, this->width(), this->height(),QPixmap(pixmap));
}