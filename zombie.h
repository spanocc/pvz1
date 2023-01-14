#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <QLabel>
#include <QMovie>
#include "helper.h"

enum ZombieType {
    ORDINARY
};

// 僵尸由mainwindow创建和销毁
class Zombie : public QLabel {

    Q_OBJECT

  public:
    Zombie(QWidget *parent);

    // 僵尸移动
    void ZombieMove();
    // 实现僵尸初始gif的播放
    void DynamicImageInit();
    // 获取僵尸当先血量
    int &hp() { return hit_point_; }
    // 击杀僵尸
    void KillZombie();

    void set_line(int line) { line_ = line; }
    const int& get_line() { return line_; }

  private:

  protected:
    ZombieType zombie_type_;
    // hp僵尸血量
    int hit_point_;
    // 僵尸攻击造成的伤害
    int damage_;
    // 僵尸所在行数
    int line_;

    Move zombie_move_; // 僵尸移动
    // 实现gif动态
    QMovie *movie_ = nullptr;

  signals:
    void Destroy(Zombie *zombie); // 告诉mianwindow销毁自己

};

#endif