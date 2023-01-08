#ifndef SEEDBANK_H
#define SEEDBANK_H

#include <vector>
#include <QWidget>
#include "plantcard.h"

class SeedBank : public QWidget {

    Q_OBJECT

  public:
    SeedBank(QWidget *parent);

    void paintEvent(QPaintEvent *);
  
  private:
    // 种子银行的参数
    static const int SeedBankWidth = 1000;
    static const int SeedBankHeight = 170;
    static const int SeedBankInitX = 20;
    static const int SeedBankInitY = 0;
    // 卡片的参数
    static const int PlantCardWidth = 120;
    static const int PlantCardHeight = 150;
    static const int PlantCardInitX = 150;
    static const int PlantCardInitY = 10;
    static const int PlantCardNum = 7;

    std::vector<PlantCard *> plant_card_vec;
};

#endif