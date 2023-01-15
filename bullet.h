#ifndef BULLET_H
#define BULLET_H

#include <QLabel>
#include <QMovie>
#include "zombie.h"
#include "helper.h"

// 子弹由MainWindow产生
class Bullet : public QLabel {

    Q_OBJECT

  public:
    Bullet(QWidget *parent);
    ~Bullet();
    // 设置行号
    void set_line(const int& line) { line_ = line; }

    // 每次MainWindow timeout,都移动子弹的位置
    void BulletMove();

    void paintEvent(QPaintEvent *);
    // 子弹击中目标
    void BulletHit(Zombie *zombie);
  private:
    static const int BulletWidth = 60;
    static const int BulletHeight = 60;

    Move bullet_move_;

    int line_; // 该子弹所处的行号
    // 子弹伤害
    int damage_;

  signals:
    void Destory(Bullet *Bullet); // 告诉mianwindow销毁自己
};

#endif