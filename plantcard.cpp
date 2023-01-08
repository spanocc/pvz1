#include "plantcard.h"

extern PlantType current_plant;

const char *plant_card_image[] = { 
/* 0  */    "",
/* 1  */    ":/image/sunflowercard.png",
};


PlantCard::PlantCard(QWidget *parent, PlantType plant_type) 
    : QPushButton(parent),
      plant_type_(plant_type) {
    
}

void PlantCard::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, this->width(), this->height(),QPixmap(plant_card_image[plant_type_]));
}

void PlantCard::ChooseCard() {
    current_plant = plant_type_;
}