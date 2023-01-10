#ifndef SUN_H
#define SUN_H

#include <QPushButton>
#include <QPainter>
#include "helper.h"


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

    Move sun_move_;
    int sun_value_;
};


#endif