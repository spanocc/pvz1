#include <iostream>
#include "peashooter.h"
#include "mainwindow.h"

extern MainWindow *main_window;

PeaShooter::PeaShooter(QWidget *parent, const QPoint& pos)  
    : Plant(parent, pos) {

    plant_type_ = PEASHOOTER;

    setFixedSize(QSize(PeaShooterWidth, PeaShooterHeight)); 
    DynamicImageInit();
    movie_->setSpeed(70);

    // 建立产生子弹的信号函数
    connect(this, &PeaShooter::ProduceBullet, main_window, &MainWindow::ProduceBullet);

    emit ProduceBullet(pos_);  
}