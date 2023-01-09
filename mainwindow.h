#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

    void paintEvent(QPaintEvent *);
    // 初始化地图
    void GraphInit();
    // 初始化阳光
    void SunInit();
    // 初始化种子银行
    void SeedBankInit();

private:
    static const int MainWindowWidth = 1800;
    static const int MainWindowHeight = 1200;

    Ui::MainWindow *ui;

    // 总计时器
    QTimer *timer_;
    // 种子银行
    SeedBank *seed_bank_;
};
#endif // MAINWINDOW_H
