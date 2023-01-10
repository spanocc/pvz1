#ifndef SUNFLOWER_H
#define SUNFLOWER_H

#include "plant.h" 

class SunFlower : public Plant {

    Q_OBJECT

  public:
    SunFlower(QWidget *parent);

  private:
    static const int SunFlowerWidth = 175;
    static const int SunFlowerHeight = 175;

};


#endif