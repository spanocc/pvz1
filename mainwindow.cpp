#include <iostream>
#include <QTimer>
#include <QPainter>
#include "mainwindow.h"
#include "./ui_mainwindow.h"




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),        
      timer_(new QTimer(this)) {

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
    Sun *asun = new Sun(this);
    connect(timer_, &QTimer::timeout, asun, &Sun::SunMove);
    connect(asun, &Sun::clicked, asun, &Sun::RecycleSun);
    connect(asun, &Sun::SignalUpdateSun, seed_bank_, &SeedBank::UpdateSun);
}


