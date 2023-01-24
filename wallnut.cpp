#include "wallnut.h"
#include "mainwindow.h"

extern MainWindow *main_window;


WallNut::WallNut(QWidget *parent, const QPoint& pos)
    : Plant(parent, pos) {

    plant_type_ = WALLNUT;
    hit_point_ = 4000;  // 4000 / 2000 / 1000

    setFixedSize(QSize(WallNutWidth, WallNutHeight)); 
    DynamicImageInit();
    movie_->setSpeed(70);

    hurt_movie_[HURT_LEVEL_0] = new QMovie(":/image/wallnut1.gif");
    hurt_movie_[HURT_LEVEL_0]->setScaledSize(this->size());
    hurt_movie_[HURT_LEVEL_0]->setSpeed(70);

    hurt_movie_[HURT_LEVEL_1] = new QMovie(":/image/wallnut2.gif");
    hurt_movie_[HURT_LEVEL_1]->setScaledSize(this->size());
    hurt_movie_[HURT_LEVEL_1]->setSpeed(70);

    connect(main_window->timer(), &QTimer::timeout, this, [this]() {
        if(hit_point_ <= 1000 && state_ != HURT_LEVEL_1) {
            state_ = HURT_LEVEL_1;
            setMovie(hurt_movie_[HURT_LEVEL_1]);
            hurt_movie_[HURT_LEVEL_1]->start();
        } else if(hit_point_ <= 2000 && hit_point_ > 1000 && state_ != HURT_LEVEL_0) {
            state_ = HURT_LEVEL_0;
            setMovie(hurt_movie_[HURT_LEVEL_0]);
            hurt_movie_[HURT_LEVEL_0]->start(); 
        }
    }); 
}