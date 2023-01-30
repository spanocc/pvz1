#ifndef PVZ_CLIENT_H
#define PVZ_CLIENT_H

#include <QThread>
#include "message.h"
#include "socket_config.h"

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
  private:
    const char *server_ip_ = nullptr;
    int server_port_;
    int epollfd_ = -1;
    int sockfd_ = -1; 

    Message read_message_;
    int read_message_offset_; // 读进来的数据相较于message_首部字段的偏移量
    Message write_message_;
    int write_message_offset_;

    int stop_ = 0; // 主循环是否停止
    int pipefd_[2]; // 通知线程结束
};


#endif