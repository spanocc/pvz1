#ifndef PEASHOOTER_H
#define PEASHOOTER_H

#include "shooter.h"

class PeaShooter : public Shooter {

    Q_OBJECT

  public:
    PeaShooter(QWidget *parent, const QPoint& pos);

  private:
    static const int PeaShooterWidth = 175;
    static const int PeaShooterHeight = 175;

};

#endif