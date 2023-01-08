#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private:
    static const int MainWindowWidth = 1800;
    static const int MainWindowHeight = 1200;

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
