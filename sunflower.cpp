#include "sunflower.h"

SunFlower::SunFlower(QWidget *parent) 
    : Plant(parent) {
    
    setFixedSize(QSize(SunFlowerWidth, SunFlowerHeight));    
}

void SunFlower::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, this->width(), this->height(),QPixmap(":/image/sunflower/sunflower0.png"));
}