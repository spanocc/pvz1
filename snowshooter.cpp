#include "snowshooter.h"
#include "mainwindow.h"

extern MainWindow *main_window;

SnowShooter::SnowShooter(QWidget *parent, const QPoint& pos) 
    : Shooter(parent, pos) {

    plant_type_ = SNOWSHOOTER;
    bullet_type_ = SNOW_BULLET;
    hit_point_ = 350;

    setFixedSize(QSize(SnowShooterWidth, SnowShooterHeight)); 
    DynamicImageInit();
    movie_->setSpeed(70);

    BulletInit();
}