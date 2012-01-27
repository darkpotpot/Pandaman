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
    Entity(int x, int y, Grid *grid, double m_update_delay);
    void set_last_update_delay(double time);
    void timed_update(double current_time, EventManager& event_manager);
    void set_update_delay(double update_delay);
    double get_update_delay();
    void set_last_update_time(double last_update_time);
    virtual bool move_to_ifp(int x, int y, EventManager& event_manager);
    virtual int get_x();
    virtual int get_y();
    //move to...
    //m_displayer.update(this)

protected:
    virtual void update(EventManager& event_manager);
    Grid *m_grid;
    int m_x;
    int m_y;
private:
    double m_update_delay;
    double m_last_update_time;
};

#endif
