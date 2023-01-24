#include <string>
#include <iostream>
#include <QPainter>
#include <QFont>
#include "seedbank.h"

// 阳光数字改变时要同时改变卡片亮度和冷却
int sun_gold = 500; // 初始阳光


SeedBank::SeedBank(QWidget *parent) 
    : QWidget(parent),
      plant_card_vec_(PlantCardNum, nullptr) {
    setFixedSize(QSize(SeedBankWidth, SeedBankHeight));
    move(QPoint(SeedBankInitX, SeedBankInitY));

    // 植物卡片
    for(int i = 0; i < PlantCardNum; ++i) {
        // 由于卡片图片不一致，为了保持对齐，所以卡片设置的高度不一样
        if(i == 0) {
            plant_card_vec_[i] = new PlantCard(this, SUNFLOWER);
            plant_card_vec_[i]->move(PlantCardInitX + PlantCard::PlantCardWidth * i, 10);  //  向日葵y轴坐标为10
        } else if(i == 1) {
            plant_card_vec_[i] = new PlantCard(this, PEASHOOTER);
            plant_card_vec_[i]->move(PlantCardInitX + PlantCard::PlantCardWidth * i, 7);   //  豌豆射手y轴坐标为7
        } else if(i == 2) {
            plant_card_vec_[i] = new PlantCard(this, SNOWSHOOTER);
            plant_card_vec_[i]->move(PlantCardInitX + PlantCard::PlantCardWidth * i, 7);   //  寒冰射手y轴坐标为7
        } else continue;

        connect(plant_card_vec_[i], &PlantCard::clicked, plant_card_vec_[i], &PlantCard::ChooseCard);
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
    // 更新数字
    sun_digit_->setText(std::to_string(sun_gold).c_str());
    // 每张卡片的亮度也要跟着改一下
     for(int i = 0; i < PlantCardNum; ++i) {
        if(plant_card_vec_[i]) {
            plant_card_vec_[i]->back_card()->update();
        }
     }
}