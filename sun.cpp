#include <cmath>
#include <iostream>
#include <string>
#include "sun.h"
#include "mainwindow.h"

extern int sun_gold;
extern MainWindow *main_window;

Sun::Sun(QWidget *parent) 
    : QPushButton(parent), 
      sun_value_(SunValue), 
      dynamic_timer_(new QTimer(this)) {
    sun_move_.vx_ = 0;
    sun_move_.vy_ = 10;
    setFixedSize(QSize(200, 200)); 
    // setIcon(QIcon(":/image/sun.png"));
    // setIconSize(QSize(100, 100));
    // setStyleSheet("QPushButton{border:none}");

    // 实现阳光动态效果
    image_num_ = 22;
    connect(dynamic_timer_, &QTimer::timeout, this, [&]() {
        current_image_ = (current_image_ + 1) % image_num_;
        update(); // 更新图像
    });
    dynamic_timer_->start(80);

    std::cout<<"produce a sun\n";
}

void Sun::SunMove() {
    QPoint sun_pos = pos();
    int x = sun_pos.x(), y = sun_pos.y();
    move(x + sun_move_.vx_, y + sun_move_.vy_);
}

void Sun::RecycleSun() {

    sun_gold += sun_value_;
    main_window->seed_bank()->UpdateSun(); // 更新剩余阳光的显示
    emit Destory(this); // 通知mainwindow销毁这个阳光

/*  QPoint sun_pos = pos();
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
    set_move(vx, vy); */
}

void Sun::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    std::string sun_path = std::string(":/image/sun/sun") + std::to_string(current_image_) + ".png";  // std::cout<<sun_path<<std::endl;
    painter.drawPixmap(0, 0, this->width(), this->height(),QPixmap(sun_path.c_str()));
}

Sun::~Sun() {
    std::cout<<"destory a sun\n";
}