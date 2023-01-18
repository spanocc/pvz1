#include <iostream>
#include "shovel.h"
#include "plant.h"
#include "mainwindow.h"

extern MainWindow *main_window;
extern PlantType current_plant;

ShovelBank::ShovelBank(QWidget *parent) : QPushButton(parent) {    
    move(1020, 0);
    setFixedSize(150, 150);

    connect(this, &ShovelBank::clicked, this, []() {
        std::cout<<"click shovelbank\n";
    });
}

void ShovelBank::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/image/shovelbank.png"));
}

Shovel::Shovel(QWidget *parent) : QWidget(parent) {    
    move(1020, 0);
    setFixedSize(150, 150);
    // 取消铲子的点击事件，使得可以越过铲子点击到后面的铲子银行
    setAttribute(Qt::WA_TransparentForMouseEvents, true);
}


void Shovel::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/image/shovel.png"));
}

void Shovel::ShovelMove() {

}

void Shovel::StartShovel() {
    // 先把current_plant恢复
    current_plant = NONEPLANT;
    main_window->DestroyPlantGhost();
}

void Shovel::ResetShovel() {

}
