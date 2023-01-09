#ifndef PLANT_H
#define PLANT_H

#include <string>
#include <QWidget>


enum PlantType {
    NONEPLANT = 0, SUNFLOWER
};

class Plant : public QWidget {

    Q_OBJECT

  public:
    Plant(QWidget *parent);

  private:
    

};




#endif