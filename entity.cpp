#include <iostream>
#include "global.h"
#include "entity.h"
#include "grid.h"

using namespace std;

Entity::Entity():CellElem(), m_x(0), m_y(0), m_grid(NULL), m_update_delay(UPDATE_TIME), m_last_update_time(0.)
{}

Entity::Entity(int x, int y, Grid *grid):CellElem(), m_x(x), m_y(y), m_grid(grid), m_update_delay(UPDATE_TIME), m_last_update_time(0.)
{}

Entity::Entity(Grid *grid):CellElem(), m_x(0), m_y(0), m_grid(grid), m_update_delay(UPDATE_TIME), m_last_update_time(0.)
{}

Entity::Entity(int x, int y, Grid *grid, double m_update_delay):CellElem(), m_x(x), m_y(y), m_grid(grid), m_update_delay(m_update_delay), m_last_update_time(0)
{}

bool Entity::move_to_ifp(int x, int y, EventManager& event_manager)
{
    if (m_grid->is_accessible(x, y))
         {
            m_grid->move(m_x, m_y, x, y, this, event_manager);
            m_x = x;
            m_y = y;
            return true;
         }
    else
        {
        return false;
        }
}

void Entity::set_update_delay(double update_delay)
{ m_update_delay = update_delay;
}

void Entity::set_last_update_time(double last_update_time)
{ m_last_update_time = last_update_time;}

void Entity::timed_update(double current_time, EventManager& event_manager)
{
    if (current_time>=m_last_update_time+m_update_delay)
    {
        update(event_manager);
        m_last_update_time = current_time;
    }
}

void Entity::update(EventManager& event_manager)
{   if (m_displayer!=NULL)
    {
   m_displayer->update(this);
   }
}

int Entity::get_x()
{ return m_x; }
int Entity::get_y()
{ return m_y; }

double Entity::get_update_delay()
{ return m_update_delay; }
