#include <iostream>
#include <QTimer>
#include <QPainter>
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "sun.h"
#include "graph.h"
#include "seedbank.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)                  
{
    ui->setupUi(this);

    setFixedSize(QSize(MainWindowWidth, MainWindowHeight));

    Graph *main_graph = new Graph(this);
    main_graph->setFixedSize(MainWindowWidth, MainWindowHeight);
    
    Sun *asun = new Sun(this);
    SeedBank *sb = new SeedBank(this);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, asun, &Sun::SunMove);
    connect(asun, &Sun::clicked, asun, &Sun::RecycleSun);
    connect(asun, &Sun::SignalUpdateSun, sb, &SeedBank::UpdateSun);
    

    timer->start(50); // 20帧
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, this->width(), this->height(),QPixmap(":/image/background1.jpg"));
}


