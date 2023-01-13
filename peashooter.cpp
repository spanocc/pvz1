#include "peashooter.h"

PeaShooter::PeaShooter(QWidget *parent)  
    : Plant(parent) {

    plant_type_ = PEASHOOTER;

    setFixedSize(QSize(PeaShooterWidth, PeaShooterHeight)); 
    DynamicImageInit();
    movie_->setSpeed(50);
}