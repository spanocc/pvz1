#ifndef SUN_H
#define SUN_H

#include <QPushButton>
#include <QPainter>
#include <QTimer>
#include "helper.h"

// 阳光的动态效果是通过切换图片实现的，因为阳光是QPushButton而不是QLable
class Sun : public QPushButton {

    Q_OBJECT

  public:
    Sun(QWidget *parent);
    ~Sun();

    void set_move(uint64_t vx, uint64_t vy) { sun_move_.vx_ = vx; sun_move_.vy_ = vy; }
    const Move& get_move() const { return sun_move_; }

    // 每次timeout,移动阳光的位置
    void SunMove();
    // 点击阳光后，回收阳光
    void RecycleSun();
    // 绘图事件 是虚函数                                                                            
    void paintEvent(QPaintEvent *);

  signals:
    void Destory(Sun *sun); // 告诉mianwindow销毁自己

  private:

    static const int RecycleSunX = 0;
    static const int RecycleSunY = 0;
    static const int SunValue = 25;

    QTimer *dynamic_timer_ = nullptr; // 实现阳光动态效果的定时器
    int image_num_ = 0; // 动态图片总数
    int current_image_ = 0; // 当前切换到第几张图片了

    Move sun_move_;
    int sun_value_;
};


#endif