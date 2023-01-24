#ifndef WALLNUT_H
#define WALLNUT_H

#include "plant.h"

class WallNut : public Plant {

    Q_OBJECT

  public:
    WallNut(QWidget *parent, const QPoint& pos);
  private:
    static const int WallNutWidth = 150;
    static const int WallNutHeight = 175;

    enum WallNutState {
        HURT_LEVEL_0 = 0, HURT_LEVEL_1, NOTHURT
    };
    WallNutState state_ = NOTHURT;
    QMovie *hurt_movie_[2] = {nullptr};
};

#endif