#include "graph_block.h"
#include "graph.h"

GraphBlock::GraphBlock(QWidget *parent) : QPushButton(parent) {
    setFixedSize(QSize(Graph::GraphBlockWidth, Graph::GraphBlockHeight)); 
    setFlat(true);
    setStyleSheet("QPushButton{background:transparent}");
}