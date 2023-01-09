#include <iostream>
#include "graph_block.h"
#include "graph.h"
#include "plant.h"
#include "sunflower.h"

extern PlantType current_plant; // 当前应该创建的植物（刚刚点击过的）

GraphBlock::GraphBlock(QWidget *parent) : QPushButton(parent) {
    setFixedSize(QSize(Graph::GraphBlockWidth, Graph::GraphBlockHeight)); 
    setFlat(true);
    setStyleSheet("QPushButton{background:transparent}");
    setStyleSheet("QPushButton{border:none}");

}

void GraphBlock::CreatPlant() {    
    if(current_plant == NONEPLANT) return;
    else if(plant_ != nullptr) return;

    else if(current_plant == SUNFLOWER) {   std::cout<<"create an sunflower\n"<<std::endl;
        SunFlower *sun_flower = new SunFlower(this);   
        sun_flower->show();
        plant_ = sun_flower;
    }
}
