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
    void DestroyPlant() { assert(plant_); delete plant_; plant_ = nullptr; }
    // 计算出行，列
    void CalculatePos();

  private:
    Plant *plant_ = nullptr;
    int line_;
    int column_;
};

#endif