#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <QLabel>
#include <QMovie>
#include "helper.h"
#include "plant.h"

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
    // 僵尸攻击植物
    void ZombieAttack(Plant *plant);
    // 僵尸受到攻击(damage_减少后就要调用该函数)
    void ZombieHit();

    void set_line(int line) { line_ = line; }
    const int& get_line() { return line_; }
    const int& get_column() { return column_; }

    void paintEvent(QPaintEvent *);

  private:

  protected:
    ZombieType zombie_type_;

    // 僵尸的状态 初始状态，正处于攻击的状态...
    enum ZombieState {
      ZOMBIE_INIT, ZOMBIE_ATTACK
    };
    int state_ = ZOMBIE_INIT;

    // hp僵尸血量
    int hit_point_;
    // 僵尸攻击造成的伤害
    int damage_;
    // 僵尸所在行数
    int line_;
    // 僵尸所在列数
    int column_;

    Move zombie_move_; // 僵尸移动
    // 实现gif动态
    QMovie *init_movie_ = nullptr;
    QMovie *attack_movie_ = nullptr;

    QTimer *init_dynamic_timer_ = nullptr; 
    int init_image_num_ = 0; // 动态图片总数
    int init_current_image_ = 0; // 当前切换到第几张图片了

    QTimer *attack_dynamic_timer_ = nullptr; 
    int attack_image_num_ = 0; // 动态图片总数
    int attack_current_image_ = 0; // 当前切换到第几张图片了
    // 是否正受到攻击
    bool hit_flag_ = false;
    QTimer *hit_timer_ = nullptr;

  signals:
    void Destroy(Zombie *zombie); // 告诉mianwindow销毁自己

};

#endif