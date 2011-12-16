#ifndef Monster_H
#define Monster_H
#include "entity.h"


class Monster:public Entity{
public:
    Monster();
    Monster(Grid *grid);
    Monster(int x, int y, Grid *grid);
    virtual void update();
    
private:
    ;
};

#endif