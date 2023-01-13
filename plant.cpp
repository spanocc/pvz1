#include <string>
#include <iostream>
#include "plant.h"

PlantType current_plant = NONEPLANT;

const char *plant_name[] = {
/* 0  */ "",
/* 1  */ "sunflower",
/* 2  */ "peashooter"
};

// 必须加上extern才能被其他文件检测到 （extern 和 const 的用法）
extern const int plant_value[] = { // 每个植物消耗的阳光  
/* 0  */ 0,
/* 1  */ 50,
/* 2  */ 100
};


Plant::Plant(QWidget *parent) 
    : QLabel(parent) {
    
}

void Plant::DynamicImageInit() {
    assert(movie_ == nullptr);
    std::string movie_path = std::string(":/image/") + plant_name[plant_type_] + ".gif";   
    movie_ = new QMovie(movie_path.c_str());
    movie_->setScaledSize(this->size());
    // movie_->setSpeed(100);  // 设置播放速度 (每个gif速度不一样，在类内单独设置)
    this->setMovie(movie_);
    movie_->start();
}


/*
void Plant::DynamicImageInit() {
    assert(dynamic_timer_);

    connect(dynamic_timer_, &QTimer::timeout, this, [&]() {
        current_image_ = (current_image_ + 1) % image_num_;
        update(); // 更新图像
    });
    dynamic_timer_->start(120);
}
*/
/*
void Plant::paintEvent(QPaintEvent *) {

    if(image_num_ == 0) return;

    QPainter painter(this);
    std::string image_path = std::string(":/image/") + plant_name[plant_type_] + "/" + plant_name[plant_type_] + std::to_string(current_image_) + ".png";
    painter.drawPixmap(0, 0, this->width(), this->height(),QPixmap(image_path.c_str()));
}
*/