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
    AddEpollIn(epollfd_, pipefd_[1], false);

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
    AddEpollIn(epollfd_, sockfd_, false);

    // Write();
    // Reset();

    epoll_event events[MAX_EVENT_NUM];
    while(1) {       
	    int event_num = epoll_wait(epollfd_, events, MAX_EVENT_NUM, -1);
		if(event_num < 0 && errno != EINTR) { // EINTR是信号把epoll_wait系统调用中断了
            std::cerr<<strerror(errno)<<std::endl;
			throw std::runtime_error("epoll failure");
		}
		for(int i = 0; i < event_num; ++i) {
			int sockfd = events[i].data.fd;
            if(sockfd == sockfd_ && (events[i].events & EPOLLIN)) { 
                if(!Read() || !ProcessRead()) {
                    CloseConnection();
                    return; // 退出线程
                }
            } else if(sockfd == pipefd_[1] && (events[i].events & EPOLLIN)) {
                Message message;
                int ret = recv(sockfd, (char *)(&message), sizeof(message), 0);
                assert(ret == sizeof(message)); // 管道一定能读成功
                assert(strcmp(message.magic, magic_str) == 0);
                if(message.message_type == CLOSE_CONNECTION) {
                    CloseConnection();
                    return; // 退出线程
                } else {
                    if(!ProcessWrite(message)) {
                        CloseConnection();
                        return; // 退出线程
                    }
                }
            }
        }
    }
}

// 可能调用多次，所以要先进行判断
void PVZClient::CloseConnection() {
    if(sockfd_ != -1) {
        // 删除事件
        epoll_ctl(epollfd_, EPOLL_CTL_DEL, sockfd_, 0);
        close(sockfd_);
        sockfd_ = -1;
    }
    std::cout<<"close the client\n";
}

void PVZClient::Reset() {
    read_message_offset_ = 0;
    write_message_offset_ = 0;
}

int PVZClient::Read() {
    int bytes_read = 0;
    while(1) { 
        if(read_message_offset_ >= sizeof(read_message_)) {
            return true; // 已经读进来一个报文了，直接返回
        }
        bytes_read = recv(sockfd_, &read_message_ + read_message_offset_, sizeof(read_message_) - read_message_offset_, 0);
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
    }
    if(strcmp(read_message_.magic, magic_str)) {
        return false;
    }
    // std::cout<<read_message_.magic<<std::endl;
    // 如果有需要回应的报文，直接发送，不要再等一轮主循环
    if(read_message_.message_type == RESPOND_CREATE_PLANT) {
        std::cout<<"create a "<<plant_name[read_message_.plant_type]<<" at ("<<read_message_.line<<", "<<read_message_.column<<")\n";
        std::cout<<"respond: "<<read_message_.respond<<std::endl;
        emit CreatePlant(read_message_.line, read_message_.column, read_message_.plant_type, read_message_.seq, read_message_.respond);
    } else if(read_message_.message_type == RESPOND_DESTROY_PLANT) {
        std::cout<<"shovel away a "<<plant_name[read_message_.plant_type]<<" at ("<<read_message_.line<<", "<<read_message_.column<<")\n";
        std::cout<<"respond: "<<read_message_.respond<<std::endl;
        emit DestroyPlant(read_message_.line, read_message_.column, read_message_.seq, read_message_.respond);
    } else if(read_message_.message_type == CREATE_ZOMBIE) {
        std::cout<<"create a zombie in line "<< read_message_.line<<"\n";
        emit CreateZombie(read_message_.zombie_type, read_message_.line);
    } else if(read_message_.message_type == PRODUCE_SUN) {
        std::cout<<"produce a sun in x: "<<read_message_.x<<"\n";
        emit ProduceSun(read_message_.x);
    } else if(read_message_.message_type == GAME_START) {
        std::cout<<"game start!\n";
        emit GameStart();
    }

    Reset();
    
    return true;
}

// 经过证明，在槽函数执行过程中，不会被其他信号打断
// 一次发就全发完
int PVZClient::Write() {
    strncpy(write_message_.magic, magic_str, sizeof(write_message_.magic) - 1);
    assert(write_message_offset_ == 0);
    int bytes_send = 0;
    while(1) {
        if(write_message_offset_ >= sizeof(write_message_)) {
            return true;
        }
        bytes_send = send(sockfd_, &write_message_ + write_message_offset_, sizeof(write_message_) - write_message_offset_, 0);
        if(bytes_send == -1) {
            if(errno == EAGAIN) { // 缓冲区暂时没有空间了， 继续等待有没有机会写
                continue;
            }
            return false;
        } else if(bytes_send == 0) {
            return false;
        }
        write_message_offset_ += bytes_send;
    }   
}

int PVZClient::ProcessWrite(const Message& message) {
    assert(write_message_offset_ == 0);
    strncpy(write_message_.magic, "yuriyuri", sizeof(write_message_.magic) - 1);

    write_message_ = message;

    if(!Write()) { // 写失败了
        std::cout<<"write failue\n";
        return false;
    }
    Reset();
    return true;
}