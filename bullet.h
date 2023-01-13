#ifndef BULLET_H
#define BULLET_H

#include <QLabel>
#include "helper.h"

// 子弹由MainWindow产生
class Bullet : public QLabel {

    Q_OBJECT

  public:
    Bullet(QWidget *parent);
    // 每次MainWindow timeout,都移动子弹的位置
    void BulletMove();

    void paintEvent(QPaintEvent *);
  private:
    static const int BulletWidth = 60;
    static const int BulletHeight = 60;

    Move bullet_move_;
};

#endif