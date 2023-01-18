#ifndef SHOVEL_H
#define SHOVEL_H

#include <QPushButton>
#include <QPainter>

class ShovelBank : public QPushButton {

    Q_OBJECT

  public:
    ShovelBank(QWidget *parent);
    void paintEvent(QPaintEvent *);
  private:

};

class Shovel : public QWidget {
    
    Q_OBJECT

  public:
    Shovel(QWidget *parent);
    void paintEvent(QPaintEvent *);
    // 铲子跟随鼠标移动
    void ShovelMove();
    // 把铲子归位
    void ResetShovel();
    // 开始让铲子跟随鼠标
    void StartShovel();
  private:
};



#endif