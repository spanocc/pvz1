#include <string>
#include <iostream>
#include <QBitmap>
#include "plantcard.h"
#include "mainwindow.h"

extern PlantType current_plant;
extern const char *plant_name[];
extern const int plant_value[];
extern const int plant_cool_down[];
extern int sun_gold;
extern MainWindow *main_window;


PlantCard::PlantCard(QWidget *parent, PlantType plant_type) 
    : QPushButton(parent),
      plant_type_(plant_type) {

    setFixedSize(QSize(PlantCardWidth, PlantCardHeight));

    // 设置一个冷却时间的特效，用两层图片来实现，PlantCard是上层，BackPlantCard是下层，图片从上往下移动，使得图片上方亮（两个叠加），下方暗（只有上面一层）
    // PlantCard的透明度
    back_card_ = new BackPlantCard(this, plant_type);
   
}

void PlantCard::paintEvent(QPaintEvent *) {
    assert(plant_type_ != NONEPLANT);
    QPainter painter(this);
    std::string card_path = std::string(":/image/") + plant_name[plant_type_] + "card.png";     // std::cout<<card_path<<std::endl;
    painter.setOpacity(0.3);
    painter.drawPixmap(0, 0, PlantCardWidth, PlantCardHeight,QPixmap(card_path.c_str()));

    // 设置透明度
    // painter.setOpacity(0.4);
    // painter.drawPixmap(0, 0, this->width(), this->height(),QPixmap(card_path.c_str()));

     //QBitmap bitmap(card_path.c_str());
     //painter.drawPixmap(0, 0, this->width(), this->height(),bitmap);
}

void PlantCard::ChooseCard() {
    // 未冷却完毕，无视点击事件
    if(back_card_->remain_cool_down_) return;
    assert(plant_type_ != NONEPLANT);
    if(current_plant == plant_type_) {  // 第一次点击是种植物，第二次点击是把current恢复到原状态
        current_plant = NONEPLANT;
        main_window->DestroyPlantGhost();
        return;
    }
    if(sun_gold >= plant_value[plant_type_]) {
        current_plant = plant_type_;
        main_window->CreatePlantGhost();
        // 把铲子关闭
        main_window->shovel()->ResetShovel();
    }
}


BackPlantCard::BackPlantCard(QWidget *parent, PlantType plant_type)
    : QWidget(parent),
      plant_type_(plant_type),
      cool_down_timer_(new QTimer(this)) {

    setFixedSize(QSize(PlantCard::PlantCardWidth, PlantCard::PlantCardHeight));
    // 将鼠标点击事件取消
    setAttribute(Qt::WA_TransparentForMouseEvents, true);
    connect(cool_down_timer_, &QTimer::timeout, this, [this]() {
        double ratio = static_cast<double>(TimeInterval) / static_cast<double>(plant_cool_down[plant_type_]);
        int height = size().height() + (ratio * PlantCard::PlantCardHeight) + 1;  // 加一是浮点数转化成整数时始终保持进位,不然最后距离达不到PlantCardHeight
        if(height >= PlantCard::PlantCardHeight) {
            height = PlantCard::PlantCardHeight;
        }
        // 冷却时间完毕
        if(remain_cool_down_ <= TimeInterval) {
            cool_down_timer_->stop();
            remain_cool_down_ = 0;
        } else remain_cool_down_ -= TimeInterval;
        // std::cout<<remain_cool_down_ <<std::endl;
        setFixedHeight(height);
        update();
    });

    // StartCoolDown();
}

void BackPlantCard::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    std::string card_path = std::string(":/image/") + plant_name[plant_type_] + "card.png";
    // 能购买并且cd == 0,则高亮这个植物卡片
    if(sun_gold >= plant_value[plant_type_] && remain_cool_down_ == 0) {
        painter.setOpacity(1);
    }
    else painter.setOpacity(0.5);
    painter.drawPixmap(0, 0, PlantCard::PlantCardWidth, PlantCard::PlantCardHeight, QPixmap(card_path.c_str()));
}

void BackPlantCard::StartCoolDown() {
    setFixedHeight(0);
    remain_cool_down_ = plant_cool_down[plant_type_];
    cool_down_timer_->start(TimeInterval);
}