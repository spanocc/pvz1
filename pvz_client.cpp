#include "pvz_client.h"


PVZClient::PVZClient(QObject *parent, const char *ip, int port) 
    : QThread(parent),
      server_ip_(ip),
      server_port_(port) {

    epollfd_ = epoll_create(1024);
    assert(epollfd_ != -1);

    int ret = socketpair(PF_UNIX, SOCK_STREAM, 0, pipefd_);
    assert(ret != -1);

    SetNoBlocking(pipefd_[0]);
    SetNoBlocking(pipefd_[1]);
    AddEpollIn(epollfd_, pipefd_[1]);

    Reset();
}

PVZClient::~PVZClient() {
    close(epollfd_);
    close(pipefd_[0]);
    close(pipefd_[1]);
}

void PVZClient::run() {
    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    inet_pton(AF_INET, server_ip_, &server_address.sin_addr);
    server_address.sin_port = htons(server_port_);

    sockfd_ = socket(PF_INET, SOCK_STREAM, 0);
    assert(sockfd_ >= 0);
    int ret = ::connect(sockfd_, (struct sockaddr*)(&server_address), sizeof(server_address)); // 加上::使用全局connect
    if(ret < 0) {
        close(sockfd_);
        throw std::runtime_error("connect failure");
    }

    SetNoBlocking(sockfd_);
    AddEpollIn(epollfd_, sockfd_);

    epoll_event events[MAX_EVENT_NUM];
    while(!stop_) {       
	    int event_num = epoll_wait(epollfd_, events, MAX_EVENT_NUM, -1);
		if(event_num < 0 && errno != EINTR) { // EINTR是信号把epoll_wait系统调用中断了
			throw std::runtime_error("epoll failure");
		}
		for(int i = 0; i < event_num; ++i) {
			int sockfd = events[i].data.fd;
            if(sockfd == sockfd_ && (events[i].events & EPOLLIN)) {
                if(Read() < 0 || ProcessRead() < 0) {
                    CloseConnection();
                }
            } else if(sockfd == pipefd_[1] && (events[i].events & EPOLLIN)) {
                char buf[16];
                memset(buf, 0, sizeof(buf));
                int ret = recv(sockfd, buf, sizeof(buf), 0);
                if(!strcmp(buf, "stop")) return; // 结束线程
            }
        }
    }
    // std::cout<<"end\n";
}

void PVZClient::CloseConnection() {
    if(sockfd_ != -1) {
        close(sockfd_);
        sockfd_ = -1;
    }
    stop_ = 1;
    // 通知结束循环
    char buf[16] = "stop";
    send(pipefd_[0], buf, sizeof(buf), 0); 
}

void PVZClient::Reset() {
    read_message_offset_ = 0;
}

int PVZClient::Read() {
    int bytes_read = 0;
    while(1) { 
        if(read_message_offset_ >= sizeof(read_message_)) {
            return true; // 已经读进来一个报文了，直接返回
        }
        bytes_read = recv(sockfd_, &read_message_, sizeof(read_message_) - read_message_offset_, 0);
        if(bytes_read == -1) {
            if(errno == EAGAIN) {
                return true; // 读完了
            }
            return false; // 
        } else if(bytes_read == 0) {
            return false; // 对方已经关闭连接
        }
        read_message_offset_ += bytes_read;
    }
}

int PVZClient::ProcessRead() {
    if(read_message_offset_ < sizeof(read_message_)) {
        return true; // 不够，继续读
    } else {
        Write();
        Reset();
    }
    return true;
}

// 经过证明，在槽函数执行过程中，不会被其他信号打断
int PVZClient::Write() {
    strcpy(write_message_.magic, "yuriyuri");
    int bytes_send = 0;
    bytes_send = send(sockfd_, &write_message_, sizeof(write_message_), 0);
    return bytes_send;
}