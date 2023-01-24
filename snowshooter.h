#ifndef SNOWSHOOTER_H
#define SNOWSHOOTER_H

#include "shooter.h"

class SnowShooter : public Shooter {

    Q_OBJECT

  public:
    SnowShooter(QWidget *parent, const QPoint& pos);
  private:
    static const int SnowShooterWidth = 175;
    static const int SnowShooterHeight = 175;
};

#endif