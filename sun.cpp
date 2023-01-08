#include <cmath>
#include "sun.h"

Sun::Sun(QWidget *parent) : QPushButton(parent) {
    sun_move_.vx_ = 0;
    sun_move_.vy_ = 10;
    setFixedSize(QSize(200, 200)); 
    // setIcon(QIcon(":/image/sun.png"));
    // setIconSize(QSize(100, 100));
    // setStyleSheet("QPushButton{border:none}");
    move(400, 0);
}

void Sun::SunMove() {
    QPoint sun_pos = pos();
    int x = sun_pos.x(), y = sun_pos.y();
    move(x + sun_move_.vx_, y + sun_move_.vy_);
}

void Sun::RecycleSun() {
    QPoint sun_pos = pos();
    int x = sun_pos.x(), y = sun_pos.y();
    int divx = x - RecycleSunX, divy = y - RecycleSunY;

    if(divx == 0) {
        set_move(0, 40);
        return;
    }

    double ratio = static_cast<double>(abs(divy)) / static_cast<double>(abs(divx)); 
    int vx = 40;
    int vy = static_cast<int>(vx * ratio);
    if(x > RecycleSunX) vx *= -1;
    if(y > RecycleSunY) vy *= -1;
    set_move(vx, vy);
}

void Sun::paintEvent(QPaintEvent *) {
     QPainter painter(this);
     painter.drawPixmap(0, 0, this->width(), this->height(),QPixmap(":/image/sun.png"));
}