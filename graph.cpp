#include <iostream>
#include "graph.h"
#include "seedbank.h"

Graph::Graph(QWidget *parent) 
    : QWidget(parent),
      graph_(LineNum, std::vector<GraphBlock *>(ColumnNum, nullptr)) {  

    for(int i = 0; i < LineNum; ++i) {  
        for(int j = 0; j < ColumnNum; ++j) {
            graph_[i][j] = new GraphBlock(this);  // 会自动delete
            graph_[i][j]->move(InitGraphX + j * GraphBlockWidth, InitGraphY + i * GraphBlockHeight);
            graph_[i][j]->CalculatePos();
        }
    } 
}


