#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <random>
#include <list>
#include <vector>
#include <QMainWindow>
#include "pvz_client.h"
#include "sun.h"
#include "bullet.h"
#include "graph.h"
#include "seedbank.h"
#include "shovel.h"
#include "sunflower.h"
#include "zombie.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent, const char *ip, int port);
    ~MainWindow();

    SeedBank *seed_bank() { return seed_bank_; }
    QTimer* timer() { return timer_; }
    std::vector<std::list<Zombie *>> &zombie_queue() { return zombie_queue_; }
    Graph *graph() { return graph_; }
    Shovel* shovel() { return shovel_; }

    void paintEvent(QPaintEvent *);
    // 初始化客户端
    void ClientInit();
    // 初始化地图
    void GraphInit();
    // 初始化阳光
    void SunInit();
    // 初始化种子银行
    void SeedBankInit();
    // 初始化铲子银行
    void ShovelBankInit();
    // 初始化僵尸生成
    void ZombieInit();

    // 产生一个掉落阳光
    void ProduceSun(int sun_x);
    // 产生一个向日葵的阳光
    void ProduceSun(const QPoint &pos);
    // 销毁这个阳光
    void DestroySun(Sun *sun) { delete sun; }

    // 产生子弹
    void ProduceBullet(const QPoint &pos, BulletType bullet_type);
    // 销毁子弹
    void DestroyBullet(Bullet *bullet) { delete bullet; }

    // 在line行生成一个zombie_type类型的僵尸
    void CreateZombie(int zombie_type, int line);
    void DestroyZombie(Zombie *zombie);

    // 创建一个跟随鼠标的植物残影
    void CreatePlantGhost();
    void DestroyPlantGhost();

    // 不设置信号函数， 都用管道来通信 , 用信号函数的话，实际上执行函数的是主线程，而不是子线程，无法做到让所有处理事件都有子线程来做的目的
    void ThreadDestroy();
    // 通知子线程发送种植植物的信息
    void SignalCreatePlant(int line, int column);
    // 收到子线程发送种植植物的信息
    void CreatePlant(int line, int column, int plant_type, int seq, bool respond);
    // 通知子线程发送铲除植物的信息
    void SignalDestroyPlant(int line, int column, int seq);
    // 收到子线程发送铲除植物的信息
    void DestroyPlant(int line, int column, int seq, bool respond);
    // 收到服务器游戏开始的通知
    void GameStart();
    // 游戏结束
    void GameDefeat();
    // 通知服务器游戏结束
    void SignalGameOver(bool victory);
    // 游戏胜利
    void GameVictory();

    // 定义为public，方便其他类获取窗口大小 eg：Sun类要获取窗口大小
    static const int MainWindowWidth = 1800;
    static const int MainWindowHeight = 1200;

    bool game_run_ = 0; // 游戏是否正在进行

private:


    Ui::MainWindow *ui;

    PVZClient *pvz_client_ = nullptr;

    // 总计时器
    QTimer *timer_ = nullptr;
    // 种子银行
    SeedBank *seed_bank_ = nullptr;
    // 铲子银行
    ShovelBank* shovel_bank_ = nullptr;
    // 铲子
    Shovel* shovel_ = nullptr;
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

    // 僵尸链表
    std::vector<std::list<Zombie *>> zombie_queue_;
    // 僵尸生成的定时器
    QTimer *zombie_timer_ = nullptr;
    // 僵尸随机出现的列数
    std::uniform_int_distribution<unsigned> zombie_u_;
    // std::default_random_engine zombie_e_;

    int pipefd_[2];

    bool last_wave_ = 0; // 是否已经达到最后一波了


};
#endif // MAINWINDOW_H
