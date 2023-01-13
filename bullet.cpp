#include <QTimer>
#include "bullet.h"
#include "mainwindow.h"

extern MainWindow *main_window;

Bullet::Bullet(QWidget *parent) : QLabel(parent) {
    bullet_move_.vx_ = 10;
    bullet_move_.vy_ = 0;

    setFixedSize(BulletWidth, BulletHeight);


}

void Bullet::BulletMove() {
    QPoint bullet_pos = pos();
    int x = bullet_pos.x(), y = bullet_pos.y();
    move(x + bullet_move_.vx_, y + bullet_move_.vy_);
}

void Bullet::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, this->width(), this->height(),QPixmap(":/image/bullet.png"));
}