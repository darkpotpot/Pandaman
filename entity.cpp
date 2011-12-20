#include <iostream>

#include "entity.h"
#include "grid.h"

using namespace std;

Entity::Entity():CellElem(), m_x(0), m_y(0), m_grid(NULL)
{}

Entity::Entity(int x, int y, Grid *grid):CellElem(), m_x(x), m_y(y), m_grid(grid)
{}

Entity::Entity(Grid *grid):CellElem(), m_x(0), m_y(0), m_grid(grid)
{}

bool Entity::move_to_ifp(int x, int y)
{
    if (m_grid->is_accessible(x, y))
         {
            m_grid->move(m_x, m_y, x, y, this);
            m_x = x;
            m_y = y;
            return true;
         }
    else
        {
        return false;
        }
}

void Entity::update()
{   if (m_displayer!=NULL)
    {
   m_displayer->update(this);
   }
}

int Entity::get_x()
{
    return m_x;
    }
int Entity::get_y(){
    return m_y;
    }
