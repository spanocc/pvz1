#include <iostream>
#include <QTimer>
#include <QTime>
#include <QPainter>
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "ordinaryzombie.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),        
      timer_(new QTimer(this)),
      e_(time(0)),
      sun_u_(0, 1500),  // 创建一个0到1500的随机数作为随机掉落的阳光的横坐标
      zombie_queue_(Graph::LineNum, std::deque<Zombie *>()),
      zombie_u_(0, 4) {

    ui->setupUi(this);

    setFixedSize(QSize(MainWindowWidth, MainWindowHeight));

    GraphInit();
    SeedBankInit();  // 种子银行后初始化，第一排的植物要在种子银行下面
    SunInit();
    ZombieInit();
    
    timer_->start(50); // 20帧
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, this->width(), this->height(),QPixmap(":/image/background1.jpg"));
}

void MainWindow::GraphInit() {
    graph_ = new Graph(this);
    graph_->setFixedSize(MainWindowWidth, MainWindowHeight);
}

void MainWindow::SeedBankInit() {
    seed_bank_ = new SeedBank(this);
}

void MainWindow::SunInit() {
    sun_timer_ = new QTimer(this);
    void (MainWindow::*produce_random_sun)() = &MainWindow::ProduceSun;  // 绑定无参数的ProduceSun
    connect(sun_timer_, &QTimer::timeout, this, produce_random_sun);
    sun_timer_->start(10000); // 每10秒产生一个阳光
}

void MainWindow::ZombieInit() {
    zombie_timer_ = new QTimer(this);
    connect(sun_timer_, &QTimer::timeout, this, [this]() {
        CreateZombie(ORDINARY, zombie_u_(e_));
    });
    sun_timer_->start(20000); // 每20秒产生一个僵尸

    CreateZombie(ORDINARY, 2);

}

void MainWindow::ProduceSun() {
    int sun_x = static_cast<int>(sun_u_(e_));   // std::cout<<sun_x<<std::endl;
    Sun *sun = new Sun(this);
    sun->move(sun_x, 0);
    connect(timer_, &QTimer::timeout, sun, &Sun::SunMove);
    connect(sun, &Sun::clicked, sun, &Sun::RecycleSun);
    connect(sun, &Sun::Destory, this, &MainWindow::DestroySun);
    sun->show();
}

void MainWindow::ProduceSun(const QPoint &pos) {   
    Sun *sun = new Sun(this);
    sun->move(pos.x(), pos.y());
    connect(sun, &Sun::clicked, sun, &Sun::RecycleSun);
    connect(sun, &Sun::Destory, this, &MainWindow::DestroySun);
    sun->show();
}

// pos参数是产生子弹的植物的GraphBlock的位置
void MainWindow::ProduceBullet(const QPoint &pos) {    // std::cout<<"produce a bullet (pos :"<<pos.x()<<" "<<pos.y()<<")\n";
    // std::cout<<pos.y()<<std::endl;
    assert(((pos.y() - Graph::InitGraphY) % Graph::GraphBlockHeight) == 0);
    int line = (pos.y() - Graph::InitGraphY) / Graph::GraphBlockHeight; // 计算出该子弹所处的行号
    assert(line >= 0 && line <= 4);

    Bullet *bullet = new Bullet(this);
    bullet->set_line(line);
    bullet->move(pos.x() + Graph::GraphBlockWidth - 50, pos.y() + 10); // -50 和 +10都是为了视觉效果
    // 子弹移动跟随mainwindow的定时器
    connect(this->timer(), &QTimer::timeout, bullet, &Bullet::BulletMove);
    // 绑定销毁子弹的函数
    connect(bullet, &Bullet::Destory, this, &MainWindow::DestroyBullet);
    bullet->show();
}

void MainWindow::CreateZombie(ZombieType zombie_type, int line) {    // std::cout<<line<<"\n";
    Zombie *zombie = nullptr;
    if(zombie_type == ORDINARY) {
        zombie = new OrdinaryZombie(this);
    }

    zombie_queue_[line].push_back(zombie);
    zombie->set_line(line);

    zombie->move(MainWindowWidth - 50, Graph::InitGraphY + line * Graph::GraphBlockHeight - 160);    
    connect(timer_, &QTimer::timeout, zombie, &Zombie::ZombieMove);
    connect(zombie, &Zombie::Destroy, this, &MainWindow::DestroyZombie);
    zombie->show();
}
