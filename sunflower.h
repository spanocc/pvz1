#ifndef SUNFLOWER_H
#define SUNFLOWER_H

#include <QTimer>
#include "plant.h" 

class SunFlower : public Plant {

    Q_OBJECT

  public:
    SunFlower(QWidget *parent);

  private:
    static const int SunFlowerWidth = 175;
    static const int SunFlowerHeight = 175;

    QTimer *produce_sun_timer_ = nullptr;

  signals:
    // 通知MainWindow产生一个阳光
    void ProduceSun(const QPoint& pos);

};


#endif