#include <string>
#include <iostream>
#include <QPainter>
#include <QFont>
#include "seedbank.h"


int sun_gold = 0;

SeedBank::SeedBank(QWidget *parent) 
    : QWidget(parent),
      plant_card_vec(PlantCardNum, nullptr) {
    setFixedSize(QSize(SeedBankWidth, SeedBankHeight));
    move(QPoint(SeedBankInitX, SeedBankInitY));

    // 卡片
    for(int i = 0; i < PlantCardNum; ++i) {
        if(i == 0) plant_card_vec[i] = new PlantCard(this, SUNFLOWER);
        else if(i == 1) plant_card_vec[i] = new PlantCard(this, PEASHOOTER);
        else continue;
        plant_card_vec[i]->setFixedSize(QSize(PlantCardWidth, PlantCardHeight));
        // 由于卡片图片不一致，为了保持对齐，所以卡片设置的高度不一样
        if(i == 0) plant_card_vec[i]->move(PlantCardInitX + PlantCardWidth * i, 10);  //  向日葵y轴坐标为10
        if(i == 1) plant_card_vec[i]->move(PlantCardInitX + PlantCardWidth * i, 7);   //  豌豆射手y轴坐标为7
        connect(plant_card_vec[i], &PlantCard::clicked, plant_card_vec[i], &PlantCard::ChooseCard);
    }
    // 阳光数字
    sun_digit_ = new QLabel(this);
    sun_digit_->move(25, 120);
    sun_digit_->setFixedSize(120, 50);
    sun_digit_->setAlignment(Qt::AlignHCenter); // 文本中心对齐

    
    QFont ft;
    ft.setPointSize(20);
    ft.setFamily("IrisUPC");
    ft.setBold(true);
    sun_digit_->setFont(ft);
    
    UpdateSun();
}

void SeedBank::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, this->width(), this->height(),QPixmap(":/image/SeedBank.png"));
}

void SeedBank::UpdateSun() { 
    sun_digit_->setText(std::to_string(sun_gold).c_str());
}