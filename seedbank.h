#ifndef SEEDBANK_H
#define SEEDBANK_H

#include <vector>
#include <QWidget>
#include <QLabel>
#include "plantcard.h"
#include "sun.h"

class SeedBank : public QWidget {

    Q_OBJECT

  public:
    SeedBank(QWidget *parent);

    void paintEvent(QPaintEvent *);

    // 更新阳光数字
    void UpdateSun();

    const std::vector<PlantCard *>& plant_card_vec() { return plant_card_vec_; }
  private:
    // 种子银行的参数
    static const int SeedBankWidth = 1000;
    static const int SeedBankHeight = 170;
    static const int SeedBankInitX = 20;
    static const int SeedBankInitY = 0;
    // 卡片的参数
    static const int PlantCardInitX = 170;
    static const int PlantCardInitY = 10;
    static const int PlantCardNum = 7;

    std::vector<PlantCard *> plant_card_vec_;

    QLabel *sun_digit_ = nullptr;
};

#endif