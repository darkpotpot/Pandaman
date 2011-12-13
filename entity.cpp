#include <iostream>

#include "entity.h"
#include "grid.h"

using namespace std;

Entity::Entity():m_x(0), m_y(0), m_grid(NULL), m_displayer(NULL)
{}

Entity::Entity(int x, int y, Grid *grid):m_x(x), m_y(y), m_grid(grid), m_displayer(NULL)
{}

Entity::Entity(Grid *grid):m_x(0), m_y(0), m_grid(grid), m_displayer(NULL)
{}

void Entity::set_displayer(Displayer * displayer)
{ m_displayer = displayer; }

void Entity::move_to_ifp(int x, int y)
{
    if (m_grid->is_accessible(x, y))
         {
            m_x = x;
            m_y = y;
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