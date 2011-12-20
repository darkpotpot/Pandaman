#ifndef Entity_H
#define Entity_H
#include "grid.h"
#include "cell.h"
#include "displayable.h"
#include "event_manager.h"


class Entity : public CellElem
{
public:
    Entity();
    Entity(Grid *grid);
    Entity(int x, int y, Grid *grid);
    virtual const CellElemType getType(){return ENTITY;};
    virtual void update(EventManager& event_manager);
    virtual bool move_to_ifp(int x, int y, EventManager& event_manager);
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
