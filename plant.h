#ifndef PLANT_H
#define PLANT_H

#include <string>
#include <QMovie>
#include <QPainter>
#include <QLabel>
#include <QTimer>

enum PlantType {
    NONEPLANT = 0, SUNFLOWER, PEASHOOTER
};

// 使用QLable的继承是要使用QMoive播放gif
// 植物的动态效果是由gif实现的
class Plant : public QLabel {

    Q_OBJECT

  public:
    Plant(QWidget *parent);

    //void paintEvent(QPaintEvent *);

    // 设置植物的位置（给pos_变量填上值）
    void set_pos(const QPoint& pos) { pos_ = pos; }
    PlantType plant_type() { return plant_type_; }
  private:
    
  protected:

    PlantType plant_type_ = NONEPLANT;

    QPoint pos_; // 相对于主窗口或者说是Graph的位置
    // 实现gif动态
    QMovie *movie_ = nullptr;

    // 实现植物动态图像
    void DynamicImageInit();

    // 改用gif实现动态效果，所以这些没用了

    //QTimer *dynamic_timer_ = nullptr; // 实现植物动态的定时器
    //int image_num_ = 0; // 动态图片总数
    //int current_image_ = 0; // 当前切换到第几张图片了

    // 实现植物动态切换图片的函数，定时器timeout时，调用该函数来切换图片
    // void ChangeImage();
    // 实现植物动态图像
    //void DynamicImageInit();
};




#endif