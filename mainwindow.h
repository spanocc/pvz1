#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <random>
#include <deque>
#include <QMainWindow>
#include "sun.h"
#include "bullet.h"
#include "graph.h"
#include "seedbank.h"
#include "sunflower.h"
#include "zombie.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    SeedBank *seed_bank() { return seed_bank_; }
    QTimer* timer() { return timer_; }
    std::deque<std::deque<Zombie *>> &zombie_queue() { return zombie_queue_; }
    Graph *graph() { return graph_; }

    void paintEvent(QPaintEvent *);
    // 初始化地图
    void GraphInit();
    // 初始化阳光
    void SunInit();
    // 初始化种子银行
    void SeedBankInit();
    // 初始化僵尸生成
    void ZombieInit();

    // 产生一个掉落阳光
    void ProduceSun();
    // 产生一个向日葵的阳光
    void ProduceSun(const QPoint &pos);
    // 销毁这个阳光
    void DestroySun(Sun *sun) { delete sun; }

    // 产生子弹
    void ProduceBullet(const QPoint &pos);
    // 销毁子弹
    void DestroyBullet(Bullet *bullet) { delete bullet; }

    // 在line行生成一个zombie_type类型的僵尸
    void CreateZombie(ZombieType zombie_type, int line);
    void DestroyZombie(Zombie *zombie) { 
        assert(zombie == zombie_queue_[zombie->get_line()].front());
        zombie_queue_[zombie->get_line()].pop_front();
        delete zombie; 
    }

    // 创建一个跟随鼠标的植物残影
    void CreatePlantGhost();
    void DestroyPlantGhost() {
        assert(plant_ghost_);
        delete plant_ghost_;
        plant_ghost_ = nullptr;
    }

    // 定义为public，方便其他类获取窗口大小 eg：Sun类要获取窗口大小
    static const int MainWindowWidth = 1800;
    static const int MainWindowHeight = 1200;

private:


    Ui::MainWindow *ui;

    // 总计时器
    QTimer *timer_ = nullptr;
    // 种子银行
    SeedBank *seed_bank_ = nullptr;
    // 地图
    Graph *graph_ = nullptr;
    // 放置植物时的残影
    PlantGhost* plant_ghost_ = nullptr;

    // 随机数引擎
    std::default_random_engine e_;

    // 掉落阳光的定时器
    QTimer *sun_timer_ = nullptr;
    // 阳光横坐标随机数
    std::uniform_int_distribution<unsigned> sun_u_;

    // 僵尸队列
    std::deque<std::deque<Zombie *>> zombie_queue_;
    // 僵尸生成的定时器
    QTimer *zombie_timer_ = nullptr;
    // 僵尸随机出现的列数
    std::uniform_int_distribution<unsigned> zombie_u_;
    std::default_random_engine zombie_e_;
};
#endif // MAINWINDOW_H
