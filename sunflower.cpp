#include "sunflower.h"

SunFlower::SunFlower(QWidget *parent) 
    : Plant(parent) {
    
    image_num_ = 18;
    plant_type_ = SUNFLOWER;

    setFixedSize(QSize(SunFlowerWidth, SunFlowerHeight));    

    DynamicImageInit();
}
