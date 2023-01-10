#ifndef PLANT_H
#define PLANT_H

#include <string>
#include <QWidget>
#include <QPainter>
#include <QTimer>

enum PlantType {
    NONEPLANT = 0, SUNFLOWER
};

class Plant : public QWidget {

    Q_OBJECT

  public:
    Plant(QWidget *parent);

    void paintEvent(QPaintEvent *);
  private:

  protected:

    PlantType plant_type_ = NONEPLANT;

    QTimer *dynamic_timer_ = nullptr; // 实现植物动态的定时器
    int image_num_ = 0; // 动态图片总数
    int current_image_ = 0; // 当前切换到第几张图片了

    // 实现植物动态切换图片的函数，定时器timeout时，调用该函数来切换图片
    // void ChangeImage();
    // 实现植物动态图像
    void DynamicImageInit();
};




#endif