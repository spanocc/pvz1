#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <QWidget>
#include "graph_block.h"

// 描述地图的类
class Graph : public QWidget {

    Q_OBJECT

  public:
    // 地图左上角坐标
    static const int InitGraphX = 100;
    static const int InitGraphY = 150;
    // 行数,列数
    static const int LineNum = 5;
    static const int ColumnNum = 9;
    
    // 每一个块的大小
    static const int GraphBlockWidth = 180;
    static const int GraphBlockHeight = 200;

    Graph(QWidget *parent);

  private:
  
    std::vector<std::vector<GraphBlock *>> graph_;  // LineNum x ColumnNum 的数组
};

#endif