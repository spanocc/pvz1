#ifndef PVZ_CLIENT_H
#define PVZ_CLIENT_H

#include <QThread>
#include "message.h"
#include "socket_config.h"

// 线程不访问全局变量

// 接收数据，发送数据，都由子线程去做

// 主线程通知子线程用的是管道
// 子线程接收到任务并处理完成后，通知主线程，直接用信号槽即可，槽函数在mainwindow中定义，信号函数在子线程中 （试过，在子线程中发信号，主线程来实现槽函数，在主线程的初始化啊函数中调用connect）

class PVZClient : public QThread{

    Q_OBJECT

  public:
    PVZClient(QObject *parent, const char *ip, int port);
    ~PVZClient();

    // 运行线程，连接服务器
    void run();
    // 关闭连接
    void CloseConnection();
    // 恢复状态
    void Reset();
    // 从套接字中读数据
    int Read();
    // 处理读进来的数据
    int ProcessRead();
    // 发送数据
    int Write();
    // 包装好将要发送的报文
    int ProcessWrite(const SignalMessage& siganl_message);

    int pipefd_[2]; //主线程用0, 子线程用1
  private:
    const char *server_ip_ = nullptr;
    int server_port_;
    int epollfd_ = -1;
    int sockfd_ = -1; 

    Message read_message_;
    int read_message_offset_; // 读进来的数据相较于message_首部字段的偏移量
    Message write_message_;
    int write_message_offset_;

};


#endif