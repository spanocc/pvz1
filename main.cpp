#include "mainwindow.h"

#include <QApplication>

#include <unistd.h>

MainWindow *main_window = nullptr;     // 设置一个指向MainWindow的全局变量指针，方便其他窗口和主窗口建立联系

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    main_window = &w; 
    w.show();
    return a.exec();
}
