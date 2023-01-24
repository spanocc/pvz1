#ifndef POTATOMINE_H
#define POTATOMINE_H

#include "plant.h"
#include "zombie.h"

class PotatoMine : public Plant {

    Q_OBJECT

  public:
    PotatoMine(QWidget *parent, const QPoint& pos);

    void PotatoBoom(Zombie *zombie);
  private:
    static const int PotatoMineWidth = 175;
    static const int PotatoMineHeight = 125;

    QTimer *grow_timer_ = nullptr;
    QMovie *grow_movie_ = nullptr;

    QTimer *boom_timer_ = nullptr;
    QMovie *boom_movie_ = nullptr;

};

#endif