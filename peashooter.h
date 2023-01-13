#ifndef PEASHOOTER_H
#define PEASHOOTER_H

#include "plant.h"

class PeaShooter : public Plant {

    Q_OBJECT

  public:
    PeaShooter(QWidget *parent);

  private:
    static const int PeaShooterWidth = 175;
    static const int PeaShooterHeight = 175;

};



#endif