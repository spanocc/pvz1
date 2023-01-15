#include <iostream>
#include "graph_block.h"
#include "graph.h"
#include "plant.h"
#include "sunflower.h"
#include "peashooter.h"
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
    
    else if(current_plant == SUNFLOWER) {   std::cout<<"create a sunflower"<<std::endl;
        SunFlower *sun_flower = new SunFlower(this, pos());   
        sun_flower->show(); // 让植物显示出来
        plant_ = sun_flower;
    }
    else if(current_plant == PEASHOOTER) {      std::cout<<"create a peashooter"<<std::endl;
        PeaShooter *pea_shooter = new PeaShooter(this, pos());
        connect(main_window->timer(), &QTimer::timeout, pea_shooter, [this, pea_shooter]() {
            // 检查这列僵尸队列中是否有僵尸在该豌豆前面
            for(int i = 0; i < main_window->zombie_queue()[pea_shooter->line()].size(); ++i) {
                int zombie_pos = main_window->zombie_queue()[pea_shooter->line()][i]->pos().x();
                int bullet_pos = pos().x() + Graph::GraphBlockWidth - 50;
                // + 180是为了视觉效果，到僵尸中心才算击中 与bullet.cpp中的BulletMove函数中的处理相同
                if(bullet_pos <= zombie_pos + 180) {
                    pea_shooter->BulletStart();
                    return;
                }
            }
            pea_shooter->BulletStop();
        });
        pea_shooter->show();
        plant_ = pea_shooter;
    }

    assert(plant_);

    sun_gold -= plant_value[plant_->plant_type()];
    main_window->seed_bank()->UpdateSun(); // 更新剩余阳光的显示
    current_plant = NONEPLANT; // 种下一个植物后，current_plant恢复到原状态

    connect(plant_, &Plant::Destroy, this, &GraphBlock::DestroyPlant);
}
