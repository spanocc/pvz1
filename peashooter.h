#ifndef PEASHOOTER_H
#define PEASHOOTER_H

#include "plant.h"

class PeaShooter : public Plant {

    Q_OBJECT

  public:
    PeaShooter(QWidget *parent, const QPoint& pos);

  private:
    static const int PeaShooterWidth = 175;
    static const int PeaShooterHeight = 175;

  signals:
    // 通知MainWindow产生一个豌豆子弹
    void ProduceBullet(const QPoint& pos);

};



#endif