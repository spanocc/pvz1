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
    // +200为了视觉效果
    if(x + 200 <= 0) {
        // std::cout<<"game over!\n";
        // emit Destroy(this);
        GameDefeat();
        return;
    }
    // 看僵尸所在格子里有没有植物            +200是为了使列数与视觉效果的列数对齐，这个数字根据实际效果来调整
    column_ = (pos().x() - Graph::InitGraphX + 200) / Graph::GraphBlockWidth;        // std::cout<<column_<<"\n";

    if(column_ >= 0 && column_ < Graph::ColumnNum) {
        Plant *plant = main_window->graph()->graph()[line_][column_]->plant();
        if(plant) {
            ZombieAttack(plant);
            return;
        } else if(state_ == ZOMBIE_ATTACK) {  // 回到INIT状态
            state_ = ZOMBIE_INIT;
            // this->setMovie(init_movie_);
            // init_movie_->start();
            attack_movie_->stop();
            init_current_image_ = 0;
            if(slow_down_) init_dynamic_timer_->start(320); // 切换图片的速度
            else init_dynamic_timer_->start(160); // 切换图片的速度
            update(); // 更新图像
        }
    }
    if(slow_down_) { // 减速，每两次移动一次（速度减半）
        slow_move_ ^= 1;
        if(slow_move_) move(x + zombie_move_.vx_, y + zombie_move_.vy_); 
    } else move(x + zombie_move_.vx_, y + zombie_move_.vy_); 
    
}

void Zombie::KillZombie() {
    emit Destroy(this);
}

void Zombie::ZombieAttack(Plant *plant) {
    int& hp = plant->hp(); 
    int damage = slow_down_ ? (damage_ / 2 + 1) : damage_;  // 减速 伤害减半 
    if(damage >= hp) {
        plant->KillPlant();
    } else {
        hp -= damage;
    }

    if(state_ == ZOMBIE_INIT) {
        state_ = ZOMBIE_ATTACK;
        // this->setMovie(attack_movie_);
        // attack_movie_->start();
        init_movie_->stop();
        attack_current_image_ = 0;
        if(slow_down_) attack_dynamic_timer_->start(320);
        else attack_dynamic_timer_->start(160);
        update(); // 更新图像
    }
}
// 僵尸被攻击后的特效
void Zombie::ZombieHit() {
    hit_flag_ = true;
    hit_timer_->start(50);
    update();
}

void Zombie::ZombieSlowDown() {
    slow_down_ = true;
    if(state_ == ZOMBIE_INIT) {  // current_image不变
        init_dynamic_timer_->stop();
        init_dynamic_timer_->start(320); // gif 播放速度变慢
    } else if(state_ == ZOMBIE_ATTACK) {
        attack_dynamic_timer_->stop();
        attack_dynamic_timer_->start(320); // gif 播放速度变慢
    }

    if(slow_down_timer_ == nullptr) {
        slow_down_timer_ = new QTimer(this);
        connect(slow_down_timer_, &QTimer::timeout, this, [this]() { // 减速结束
            slow_down_timer_->stop();
            slow_down_ = false;
            slow_move_ = false;

            if(state_ == ZOMBIE_INIT) {  // current_image不变
                init_dynamic_timer_->stop();
                init_dynamic_timer_->start(160); // gif 播放速度复原
            } else if(state_ == ZOMBIE_ATTACK) {
                attack_dynamic_timer_->stop();
                attack_dynamic_timer_->start(160); 
            }
        });
    }

    slow_down_timer_->stop();
    slow_down_timer_->start(3000); // 刷新减速时间为3秒

}

void Zombie::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    QPixmap pixmap;
    QImage image;
    if(state_ == ZOMBIE_INIT) {
        init_movie_->jumpToFrame(init_current_image_);
        image = init_movie_->currentImage();
    }
    else if(state_ == ZOMBIE_ATTACK) {
        attack_movie_->jumpToFrame(attack_current_image_);
        image = attack_movie_->currentImage();    
    }

    if(slow_down_) {
            // 给图片变蓝,寒冰的特效
        int r, g, b;
        QColor old_color;
        for(int x = 0; x < image.width(); ++x) {
            for(int y = 0; y < image.height(); ++y) { 
                old_color = QColor(image.pixel(x, y));
                r = old_color.red();
                g = old_color.green(); 
                b = old_color.blue();         
                if(!r & !g & !b) continue;; // 透明颜色不变色  
                b += 70; 
                if(b > 255) b = 255; 
                image.setPixelColor(x, y, qRgb(r, g, b));
            }
        }
    }


    if(hit_flag_) painter.setOpacity(0.5);
    painter.drawPixmap(0, 0, this->width(), this->height(), QPixmap::fromImage(image));
}
