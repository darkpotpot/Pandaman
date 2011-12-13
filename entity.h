#ifndef Entity_H
#define Entity_H
#include "grid.h"
#include "displayable.h"

class Entity : public Displayable
{
public:
    Entity();
    Entity(Grid *grid);
    Entity(int x, int y, Grid *grid);
    virtual void update();
    virtual void move_to_ifp(int x, int y);
    virtual int get_x();
    virtual int get_y();
    //move to...
    //m_displayer.update(this)

protected:
    Grid *m_grid;
    int m_x;
    int m_y;
};

#endif
