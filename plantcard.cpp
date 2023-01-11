#include <string>
#include <iostream>
#include "plantcard.h"

extern PlantType current_plant;
extern const char *plant_name[];
extern const int plant_value[];
extern int sun_gold;


PlantCard::PlantCard(QWidget *parent, PlantType plant_type) 
    : QPushButton(parent),
      plant_type_(plant_type) {
        
}

void PlantCard::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    std::string card_path = std::string(":/image/") + plant_name[plant_type_] + "card.png";     // std::cout<<card_path<<std::endl;
    painter.drawPixmap(0, 0, this->width(), this->height(),QPixmap(card_path.c_str()));
}

void PlantCard::ChooseCard() {
    if(current_plant == plant_type_) {  // 第一次点击是种植物，第二次点击是把current恢复到原状态
        current_plant = NONEPLANT;
        return;
    }
    if(sun_gold >= plant_value[plant_type_]) current_plant = plant_type_;
}