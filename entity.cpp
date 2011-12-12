#include <iostream>

#include "entity.h"
#include "grid.h"

using namespace std;

Entity::Entity():m_x(0), m_y(0), m_grid(NULL)
{}

Entity::Entity(int x, int y, Grid *grid):m_x(x), m_y(y), m_grid(grid)
{}

Entity::Entity(Grid *grid):m_x(0), m_y(0), m_grid(grid)
{}

void Entity::update()
{

}