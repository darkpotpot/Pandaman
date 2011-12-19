#include "monster.h"
#include <stdlib.h>
#include <time.h>

#include <iostream>

using namespace std;
Monster::Monster():Entity()
{}

Monster::Monster(Grid *grid):Entity(grid)
{}

Monster::Monster(int x, int y, Grid *grid):Entity(x, y, grid)
{}

void Monster::update()
{
    int x;
    int y;
    m_ia.compute_movement(this, m_grid, x, y);
    Entity::move_to_ifp(x, y );
    Entity::update();
}