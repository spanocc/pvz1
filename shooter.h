#ifndef SHOOTER_H
#define SHOOTER_H

#include "plant.h"
#include "bullet.h"

class Shooter : public Plant {

    Q_OBJECT

  public:
    Shooter(QWidget *parent, const QPoint& pos);

    // 如果该行有僵尸，开始射子弹
    void BulletStart();
    // 停止射子弹
    void BulletStop();
    // 子弹初始化要在子类中使用，不能在Shooter的构造函数中来用，否则子类也需要声明BulletStart BulletStop ProduceBullet 这三个函数才能使用
    void BulletInit();

  protected:
    QTimer *produce_bullet_timer_ = nullptr;
    // 定时器开关，表示当前是否处于发射子弹的状态
    bool produce_bullet_switch_ = false;

    BulletType bullet_type_ = ORDINARY_BULLET; // 产生的子弹类型

  signals:
    // 通知MainWindow产生一个子弹
    void ProduceBullet(const QPoint& pos, BulletType bullet_type);
  
};

#endif
