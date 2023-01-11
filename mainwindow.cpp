#include <iostream>
#include <QTimer>
#include <QTime>
#include <QPainter>
#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),        
      timer_(new QTimer(this)),
      sun_u_(0, 1500),  // 创建一个0到1500的随机数作为随机掉落的阳光的横坐标
      sun_e_(time(0)) {

    ui->setupUi(this);

    setFixedSize(QSize(MainWindowWidth, MainWindowHeight));

    GraphInit();
    SeedBankInit();  // 种子银行后初始化，第一排的植物要在种子银行下面
    SunInit();
    
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
    Graph *main_graph = new Graph(this);
    main_graph->setFixedSize(MainWindowWidth, MainWindowHeight);
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

void MainWindow::ProduceSun() {
    int sun_x = static_cast<int>(sun_u_(sun_e_));   // std::cout<<sun_x<<std::endl;
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
