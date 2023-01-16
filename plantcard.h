#ifndef PLANTCARD_H
#define PLANTCARD_H

#include <QPushButton>
#include <QImage>
#include <QPainter>
#include "plant.h"

class BackPlantCard;

class PlantCard : public QPushButton {

    Q_OBJECT

  public:
    PlantCard(QWidget *parent, PlantType plant_type);

    void paintEvent(QPaintEvent *);

    void ChooseCard();

    BackPlantCard* back_card() { return back_card_; }
    PlantType plant_type() { return plant_type_; }

    static const int PlantCardWidth = 115;
    static const int PlantCardHeight = 145;

  private:

    PlantType plant_type_ = NONEPLANT;
    BackPlantCard* back_card_;
};

class BackPlantCard : public QWidget {

friend PlantCard;

    Q_OBJECT

  public:
    BackPlantCard(QWidget *parent, PlantType plant_type);

    void paintEvent(QPaintEvent *);
    // 开始冷却
    void StartCoolDown();

    static const int TimeInterval = 100; // 定时器0.1s一次

  private:

    PlantType plant_type_ = NONEPLANT;

    // 植物剩余的冷却时间
    int remain_cool_down_ = 0;

    QTimer *cool_down_timer_ = nullptr;
};

#endif