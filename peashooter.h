#ifndef PEASHOOTER_H
#define PEASHOOTER_H

#include "plant.h"

class PeaShooter : public Plant {

    Q_OBJECT

  public:
    PeaShooter(QWidget *parent, const QPoint& pos);
    // 如果该行有僵尸，开始射子弹
    void BulletStart();
    // 停止设子弹
    void BulletStop();

  private:
    static const int PeaShooterWidth = 175;
    static const int PeaShooterHeight = 175;

    QTimer *produce_bullet_timer_ = nullptr;
    // 定时器开关，表示当前是否处于发射子弹的状态
    bool produce_bullet_switch_ = false;

  signals:
    // 通知MainWindow产生一个豌豆子弹
    void ProduceBullet(const QPoint& pos);

};



#endif