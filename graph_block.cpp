#include <iostream>
#include "graph_block.h"
#include "graph.h"
#include "plant.h"
#include "sunflower.h"
#include "peashooter.h"
#include "snowshooter.h"
#include "mainwindow.h"
#include "shovel.h"

extern MainWindow *main_window; 
extern PlantType current_plant; // 当前应该创建的植物（刚刚点击过的）
extern int sun_gold;
extern const int plant_value[];
extern bool shovel_switch;

GraphBlock::GraphBlock(QWidget *parent) : QPushButton(parent) {
    setFixedSize(QSize(Graph::GraphBlockWidth, Graph::GraphBlockHeight)); 
    setFlat(true);
    setStyleSheet("QPushButton{background:transparent}");
    setStyleSheet("QPushButton{border:none}");

    connect(this, &GraphBlock::clicked, this, [this]() {
        if(shovel_switch) {
            if(plant_) DestroyPlant();
            main_window->shovel()->ResetShovel();
        } else CreatPlant();
    });
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
        /*connect(main_window->timer(), &QTimer::timeout, pea_shooter, [this, pea_shooter]() {
            // 检查这列僵尸队列中是否有僵尸在该豌豆前面
            for(const auto& it: main_window->zombie_queue()[pea_shooter->line()]) {
                int zombie_pos = it->pos().x();
                int bullet_pos = pos().x() + Graph::GraphBlockWidth - 50;
                // + 180是为了视觉效果，到僵尸中心才算击中 与bullet.cpp中的BulletMove函数中的处理相同
                if(bullet_pos <= zombie_pos + 180) {
                    pea_shooter->BulletStart();
                    return;
                }
            }
            pea_shooter->BulletStop();
        });*/
        pea_shooter->show();
        plant_ = pea_shooter;
    }
    else if(current_plant == SNOWSHOOTER) {   std::cout<<"create a snowshooter"<<std::endl;
        SnowShooter *snow_shooter = new SnowShooter(this, pos());
        snow_shooter->show();
        plant_ = snow_shooter;
    }

    assert(plant_);

    sun_gold -= plant_value[plant_->plant_type()];
    main_window->seed_bank()->UpdateSun(); // 更新剩余阳光的显示
    // 卡片开始冷却
    const auto& pcv = main_window->seed_bank()->plant_card_vec();
    for(const auto& it : pcv) {
        if(it && it->plant_type() == current_plant) {
            it->back_card()->StartCoolDown();
            break;
        }
    }

    current_plant = NONEPLANT; // 种下一个植物后，current_plant恢复到原状态
    main_window->DestroyPlantGhost();

    connect(plant_, &Plant::Destroy, this, &GraphBlock::DestroyPlant);
}
