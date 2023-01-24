#include <iostream>
#include <vector>
#include "potatomine.h"
#include "mainwindow.h"

extern MainWindow *main_window;

PotatoMine::PotatoMine(QWidget *parent, const QPoint& pos) 
    : Plant(parent, pos),
      grow_timer_(new QTimer(this)),
      boom_timer_(new QTimer(this)) {

    plant_type_ = POTATOMINE;
    hit_point_ = 350;
    damage_ = 1800;

    setFixedSize(QSize(PotatoMineWidth, PotatoMineHeight)); 
    DynamicImageInit();
    movie_->setSpeed(70);
    // 长大后的土豆地雷
    grow_movie_ = new QMovie(":/image/potatomine1.gif");
    grow_movie_->setScaledSize(this->size());
    grow_movie_->setSpeed(70);  // 设置播放速度 (每个gif速度不一样，在类内单独设置)
    // 爆炸特效
    boom_movie_ = new QMovie(":/image/potatoboom.gif");
    boom_movie_->setScaledSize(this->size());
    boom_movie_->setSpeed(70);

    // 土豆地雷长出来
    connect(grow_timer_, &QTimer::timeout, this, [this]() {
        setMovie(grow_movie_);
        grow_movie_->start();
        grow_timer_->stop();

        connect(main_window->timer(), &QTimer::timeout, this, [this]() {
            bool flag = false;
            std::vector<Zombie *> attacked_zombie; // 保存会被炸到的僵尸
            for(const auto& it: main_window->zombie_queue()[line()]) {
                if(it->get_column() == column_) {
                    attacked_zombie.push_back(it);
                    // PotatoBoom(it); 不能边遍历边删除
                    flag = true;
                }
            }
            if(flag) {  
                for(const auto& it: attacked_zombie) {
                    PotatoBoom(it);
                }
                setMovie(boom_movie_);   
                boom_movie_->start();  
                boom_timer_->start(500);  
            }
        });
    });

    connect(boom_timer_, &QTimer::timeout, this, [this]() {    
        boom_timer_->stop();
        emit Destroy();     
    });

    grow_timer_->start(10000);
    

}

void PotatoMine::PotatoBoom(Zombie *zombie) {   
    int &hp = zombie->hp();
    if(hp <= damage_) {
        zombie->KillZombie();
    } else {
        hp -= damage_;
    }                                           
}