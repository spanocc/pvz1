#include "mainwindow.h"

#include <QApplication>

#include <unistd.h>

MainWindow *main_window = nullptr;     // 设置一个指向MainWindow的全局变量指针，方便其他窗口和主窗口建立联系
const char *server_ip = "192.168.48.130";
const int server_port = 2200;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w(nullptr, server_ip, server_port);
    main_window = &w; 
    w.show();
    return a.exec();
}
