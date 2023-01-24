#ifndef PLANT_H
#define PLANT_H

#include <string>
#include <QMovie>
#include <QPainter>
#include <QLabel>
#include <QTimer>

enum PlantType {
    NONEPLANT = 0, SUNFLOWER, PEASHOOTER, SNOWSHOOTER
};

// 使用QLable的继承是要使用QMoive播放gif
// 植物的动态效果是由gif实现的
class Plant : public QLabel {

    Q_OBJECT

  public:
    Plant(QWidget *parent, const QPoint& p);

    //void paintEvent(QPaintEvent *);
    PlantType plant_type() { return plant_type_; }

    // 杀死植物
    void KillPlant();

    int& hp() { return hit_point_; }
    const int& line() { return line_; }
    const int& column() { return column_; }
  private:
    
  protected:

    PlantType plant_type_ = NONEPLANT;

    // hp植物血量
    int hit_point_;

    int line_; // 植物所在行数
    int column_; // 植物所在列数

    QPoint pos_; // 相对于主窗口或者说是Graph的位置
    // 实现gif动态
    QMovie *movie_ = nullptr;

    // 实现植物动态图像
    void DynamicImageInit();

  signals:
    void Destroy();

    // 改用gif实现动态效果，所以这些没用了

    //QTimer *dynamic_timer_ = nullptr; // 实现植物动态的定时器
    //int image_num_ = 0; // 动态图片总数
    //int current_image_ = 0; // 当前切换到第几张图片了

    // 实现植物动态切换图片的函数，定时器timeout时，调用该函数来切换图片
    // void ChangeImage();
    // 实现植物动态图像
    //void DynamicImageInit();
};

// 点击植物卡片后，放置植物之前，鼠标位置出现这个植物的残影
class PlantGhost : public QWidget {
  
	Q_OBJECT

  public:
	PlantGhost(QWidget *parent);

	void paintEvent(QPaintEvent *);

	void PlantGhostMove();
  private:
};



#endif