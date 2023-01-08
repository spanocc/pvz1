#include <QPainter>
#include "seedbank.h"

SeedBank::SeedBank(QWidget *parent) 
    : QWidget(parent),
      plant_card_vec(PlantCardNum, nullptr) {
    setFixedSize(QSize(SeedBankWidth, SeedBankHeight));
    move(QPoint(SeedBankInitX, SeedBankInitY));

    
    for(int i = 0; i < PlantCardNum; ++i) {
        plant_card_vec[i] = new PlantCard(this, SUNFLOWER);
        plant_card_vec[i]->setFixedSize(QSize(PlantCardWidth, PlantCardHeight));
        plant_card_vec[i]->move(PlantCardInitX + PlantCardWidth * i, 10);
    }
}

void SeedBank::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, this->width(), this->height(),QPixmap(":/image/SeedBank.png"));
}