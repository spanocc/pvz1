#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <random>
#include <QMainWindow>
#include "sun.h"
#include "graph.h"
#include "seedbank.h"
#include "sunflower.h"

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

    void paintEvent(QPaintEvent *);
    // 初始化地图
    void GraphInit();
    // 初始化阳光
    void SunInit();
    // 初始化种子银行
    void SeedBankInit();

    // 产生一个掉落阳光
    void ProduceSun();
    // 产生一个向日葵的阳光
    void ProduceSun(const QPoint &pos);
    // 销毁这个阳光
    void DestroySun(Sun *sun) { delete sun; }

    // 定义为public，方便其他类获取窗口大小 eg：Sun类要获取窗口大小
    static const int MainWindowWidth = 1800;
    static const int MainWindowHeight = 1200;

private:


    Ui::MainWindow *ui;

    // 总计时器
    QTimer *timer_ = nullptr;
    // 种子银行
    SeedBank *seed_bank_ = nullptr;


    // 掉落阳光的计时器
    QTimer *sun_timer_ = nullptr;
    // 阳光横坐标随机数
    std::uniform_int_distribution<unsigned> sun_u_;
    std::default_random_engine sun_e_;



};
#endif // MAINWINDOW_H
