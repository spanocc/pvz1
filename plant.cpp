#include <string>
#include <iostream>
#include "plant.h"
#include "graph.h"
#include "mainwindow.h"

// current_plant改变时要同时改变鼠标位置的植物残影
PlantType current_plant = NONEPLANT;
extern MainWindow *main_window;

const char *plant_name[] = {
/* 0  */ "",
/* 1  */ "sunflower",
/* 2  */ "peashooter",
/* 3  */ "snowshooter",
/* 4  */ "potatomine",
/* 5  */ "wallnut",
};

// 必须加上extern才能被其他文件检测到 （extern 和 const 的用法）
extern const int plant_value[] = { // 每个植物消耗的阳光  
/* 0  */ 0,
/* 1  */ 50,
/* 2  */ 100,
/* 3  */ 175,
/* 4  */ 25,
/* 5  */ 50,
};

extern const int plant_cool_down[] = { // 每个植物冷却时间 （毫秒）
/* 0  */ 5000,
/* 1  */ 5000,
/* 2  */ 5000,
/* 3  */ 5000,
/* 4  */ 5000,
/* 5  */ 5000,

};


Plant::Plant(QWidget *parent, const QPoint& pos) 
    : QLabel(parent), 
      pos_(pos) {  // pos是相对于主窗口的位置
    // 算出行数和列数
    assert(((pos.y() - Graph::InitGraphY) % Graph::GraphBlockHeight) == 0);
    assert(((pos.x() - Graph::InitGraphX) % Graph::GraphBlockWidth) == 0);
    line_ = (pos.y() - Graph::InitGraphY) / Graph::GraphBlockHeight; // 计算出该子弹所处的行号
    column_ = (pos.x() - Graph::InitGraphX) / Graph::GraphBlockWidth;
    assert(line_ >= 0 && line_ < Graph::LineNum);
    assert(column_ >= 0 && column_ < Graph::ColumnNum);

    // std::cout<<line_<<" "<<column_<<std::endl;
}

void Plant::DynamicImageInit() {
    assert(movie_ == nullptr);
    std::string movie_path = std::string(":/image/") + plant_name[plant_type_] + ".gif";   
    movie_ = new QMovie(movie_path.c_str());
    movie_->setScaledSize(this->size());
    // movie_->setSpeed(100);  // 设置播放速度 (每个gif速度不一样，在类内单独设置)
    this->setMovie(movie_);
    movie_->start();
}

void Plant::KillPlant() {
    emit Destroy();
}

PlantGhost::PlantGhost(QWidget *parent) : QWidget(parent){
    setFixedSize(QSize(175, 175));
    if(current_plant == POTATOMINE) setFixedSize(QSize(175, 125));
    else if(current_plant == WALLNUT) setFixedSize(QSize(150, 175));
    // 将鼠标点击事件取消
    setAttribute(Qt::WA_TransparentForMouseEvents, true);

    std::cout<<"creat plantghost\n";
}

void PlantGhost::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    std::string plant_path = std::string(":/image/") + plant_name[current_plant] + ".gif";  
    if(current_plant == POTATOMINE) plant_path = ":/image/potatomine1.gif";
    painter.setOpacity(0.3);
    painter.drawPixmap(0, 0, this->width(), this->height(),QPixmap(plant_path.c_str()));
}

void  PlantGhost::PlantGhostMove() {
    QPoint mouse_pos = QCursor::pos(); // 鼠标的绝对位置
    int x = mouse_pos.x() - main_window->pos().x(), y = mouse_pos.y() - main_window->pos().y(); // 鼠标相对于主屏幕的位置
    move(x - 100, y - 100);
    // std::cout<<x<<" "<<y<<std::endl;
}

/*
void Plant::DynamicImageInit() {
    assert(dynamic_timer_);

    connect(dynamic_timer_, &QTimer::timeout, this, [&]() {
        current_image_ = (current_image_ + 1) % image_num_;
        update(); // 更新图像
    });
    dynamic_timer_->start(120);
}
*/
/*
void Plant::paintEvent(QPaintEvent *) {

    if(image_num_ == 0) return;

    QPainter painter(this);
    std::string image_path = std::string(":/image/") + plant_name[plant_type_] + "/" + plant_name[plant_type_] + std::to_string(current_image_) + ".png";
    painter.drawPixmap(0, 0, this->width(), this->height(),QPixmap(image_path.c_str()));
}
*/