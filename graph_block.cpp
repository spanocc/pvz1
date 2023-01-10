#include <iostream>
#include "graph_block.h"
#include "graph.h"
#include "plant.h"
#include "sunflower.h"
#include "mainwindow.h"

extern MainWindow *main_window; 
extern PlantType current_plant; // 当前应该创建的植物（刚刚点击过的）
extern int sun_gold;
extern const int plant_value[];

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
        sun_flower->show(); // 让植物显示出来
        plant_ = sun_flower;
    }

    assert(plant_);
    plant_->set_pos(pos());
    sun_gold -= plant_value[plant_->plant_type()];
    main_window->seed_bank()->UpdateSun(); // 更新剩余阳光的显示
}
