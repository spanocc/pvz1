#ifndef GRAPH_BLOCK_H
#define GRAPH_BLOCK_H

#include <QPushButton>
#include <QPainter>
#include <plant.h>

class GraphBlock : public QPushButton {

  Q_OBJECT

  public:
    GraphBlock(QWidget *parent);

    Plant* plant() { return plant_; }

    // 在此处创建一个植物
    void CreatPlant();
    // 销毁一个植物
    void DestroyPlant(); 
    // 计算出行，列
    void CalculatePos();

    // 接收到报文， 创建一个植物
    void CreatePlant(int plant_type, int seq, bool respond);
    // 接收到报文， 销毁植物
    void DestroyPlant(int seq, bool respond);

  private:
    Plant *plant_ = nullptr;
    int line_;
    int column_;
    int seq_ = 0;
};

#endif