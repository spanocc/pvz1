#include <iostream>
#include "shovel.h"
#include "plant.h"
#include "mainwindow.h"

extern MainWindow *main_window;
extern PlantType current_plant;

bool shovel_switch = false;

ShovelBank::ShovelBank(QWidget *parent) : QPushButton(parent) {    
    move(1020, 0);
    setFixedSize(150, 150);

    connect(this, &ShovelBank::clicked, this, []() {
        if(!main_window->game_run) return; // 游戏未开始，无视点击事件
        std::cout<<"click shovelbank\n";
        if(!shovel_switch) main_window->shovel()->StartShovel();
        else main_window->shovel()->ResetShovel();
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
    QPoint mouse_pos = QCursor::pos(); // 鼠标的绝对位置
    int x = mouse_pos.x() - main_window->pos().x(), y = mouse_pos.y() - main_window->pos().y(); // 鼠标相对于主屏幕的位置
    move(x - 100, y - 100);
}

void Shovel::StartShovel() {
    if(shovel_switch == true) return;
    // 先把current_plant恢复
    current_plant = NONEPLANT;
    main_window->DestroyPlantGhost();

    shovel_switch = true;

    connect(main_window->timer(), &QTimer::timeout, this, &Shovel::ShovelMove);
}

void Shovel::ResetShovel() {
    if(shovel_switch == false) return;
    disconnect(main_window->timer(), &QTimer::timeout, this, &Shovel::ShovelMove);
    move(1020, 0);
    shovel_switch = false;
}
