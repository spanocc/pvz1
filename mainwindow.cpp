#include <iostream>
#include <algorithm>
#include <QTimer>
#include <QTime>
#include <QPainter>
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "ordinaryzombie.h"

extern PlantType current_plant;

MainWindow::MainWindow(QWidget *parent, const char *ip, int port)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),  
      pvz_client_(new PVZClient(this, ip, port)),
      timer_(new QTimer(this)),
      e_(time(0)),
      sun_u_(0, 1500),  // 创建一个0到1500的随机数作为随机掉落的阳光的横坐标
      zombie_queue_(Graph::LineNum, std::list<Zombie *>()),
      zombie_u_(0, 4) {

    ui->setupUi(this);

    setFixedSize(QSize(MainWindowWidth, MainWindowHeight));

    // 在初始化地图之前可以播放开始界面

    GraphInit();
    SeedBankInit();  // 种子银行后初始化，第一排的植物要在种子银行下面
    ShovelBankInit();
    SunInit();
    ZombieInit();
    
    timer_->start(50); // 20帧

    ClientInit();
    
}

MainWindow::~MainWindow()
{
    delete ui;
    ThreadDestroy();
    pvz_client_->exit();
    pvz_client_->wait();
    delete pvz_client_;
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

void MainWindow::ShovelBankInit() {
    shovel_bank_ = new ShovelBank(this);
    shovel_ = new Shovel(this);
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
void MainWindow::ProduceBullet(const QPoint &pos, BulletType bullet_type) {    // std::cout<<"produce a bullet (pos :"<<pos.x()<<" "<<pos.y()<<")\n";
    // std::cout<<pos.y()<<std::endl;
    assert(((pos.y() - Graph::InitGraphY) % Graph::GraphBlockHeight) == 0);
    int line = (pos.y() - Graph::InitGraphY) / Graph::GraphBlockHeight; // 计算出该子弹所处的行号
    assert(line >= 0 && line <= 4);

    Bullet *bullet = new Bullet(this, bullet_type);
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

    // 将鼠标点击事件取消
    zombie->setAttribute(Qt::WA_TransparentForMouseEvents, true);  // 防止僵尸档到GraphBlock的按钮
}

void MainWindow::DestroyZombie(Zombie *zombie) { 
    auto& zombie_list = zombie_queue_[zombie->get_line()];
    const auto& it = std::find(zombie_list.begin(), zombie_list.end(), zombie);
    assert(it != zombie_list.end());
    zombie_list.erase(it);
    delete zombie; 
}


void MainWindow::CreatePlantGhost() {
    assert(current_plant != NONEPLANT);
    // 第一次选择植物
    if(plant_ghost_ == nullptr) {
        plant_ghost_ = new PlantGhost(this);
        connect(this->timer_, &QTimer::timeout, plant_ghost_, &PlantGhost::PlantGhostMove);
        plant_ghost_->show();
    }
    // 之前已经选了一个植物，现在是更换植物
    else plant_ghost_->update();
}
void MainWindow::DestroyPlantGhost() { 
    if(plant_ghost_ == nullptr) return;
    assert(current_plant == NONEPLANT);
    delete plant_ghost_;
    plant_ghost_ = nullptr;
 }

void MainWindow::ClientInit() {
    // connect(pvz_client_, &PVZClient::pausss, this, &MainWindow::Pausss);
    // connect(this, &MainWindow::SignalProcessWrite, pvz_client_, &PVZClient::ProcessWrite);
    // connect(this, SIGNAL(SignalProcessWrite(const SignalMessage&)), pvz_client_, SLOT(ProcessWrite(const SignalMessage&)));
    connect(pvz_client_, &PVZClient::CreatePlant, this, &MainWindow::CreatePlant);
    connect(pvz_client_, &PVZClient::DestroyPlant, this, &MainWindow::DestroyPlant);
    pvz_client_->start();
}

void MainWindow::ThreadDestroy() {
    Message message;
    strncpy(message.magic, magic_str, sizeof(message.magic) - 1);
    message.message_type = CLOSE_CONNECTION;
    send(pvz_client_->pipefd_[0], (char *)(&message), sizeof(message), 0);
}

void MainWindow::SignalCreatePlant(int line, int column) {
    assert(current_plant != NONEPLANT);
    // 发送报文
    Message message;
    strncpy(message.magic, magic_str, sizeof(message.magic) - 1);
    message.message_type = SIGNAL_CREATE_PLANT;
    message.line = line;
    message.column = column;
    message.plant_type = current_plant;
    
    int ret = send(pvz_client_->pipefd_[0], (char *)(&message), sizeof(message), 0);
    assert(ret == sizeof(message));
}

void MainWindow::CreatePlant(int line, int column, int plant_type, int seq, bool respond) {
    assert(line >= 0 && line < Graph::LineNum && column >= 0 && column < Graph::ColumnNum);
    graph_->graph()[line][column]->CreatePlant(plant_type, seq, respond);
}

void MainWindow::SignalDestroyPlant(int line, int column, int seq) {
    // 发送报文
    Message message;
    strncpy(message.magic, magic_str, sizeof(message.magic) - 1);
    message.message_type = SIGNAL_DESTROY_PLANT;
    message.line = line;
    message.column = column;
    message.seq = seq;
    
    int ret = send(pvz_client_->pipefd_[0], (char *)(&message), sizeof(message), 0);
    assert(ret == sizeof(message));
}

void MainWindow::DestroyPlant(int line, int column, int seq, bool respond) {
    assert(line >= 0 && line < Graph::LineNum && column >= 0 && column < Graph::ColumnNum);
    graph_->graph()[line][column]->DestroyPlant(seq, respond);
}
