#ifndef ORDINARYZOMBIE_H
#define ORDINARYZOMBIE_H

#include "zombie.h"

class OrdinaryZombie : public Zombie {

    Q_OBJECT

  public:
    OrdinaryZombie(QWidget *parent);

  private:
    static const int OrdinaryZombieWidth = 350;
    static const int OrdinaryZombieHeight = 350;
};

#endif