#ifndef PLANTCARD_H
#define PLANTCARD_H

#include <QPushButton>
#include <QPainter>
#include "plant.h"


class PlantCard : public QPushButton {

    Q_OBJECT

  public:
    PlantCard(QWidget *parent, PlantType plant_type);

    void paintEvent(QPaintEvent *);

    void ChooseCard();

  private:

    PlantType plant_type_ = NONEPLANT;

};

#endif