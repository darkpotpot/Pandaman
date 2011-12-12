#ifndef Entity_H
#define Entity_H
#include "grid.h"
class Entity
{
public:
    Entity();
    Entity(Grid *grid);
    Entity(int x, int y, Grid *grid);
    void update();
    //move to...
    //m_displayer.update(this)
    int m_x;
    int m_y;
private:
    Grid *m_grid;
};

#endif