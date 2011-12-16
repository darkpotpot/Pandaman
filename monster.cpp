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
    //TODO : later call an IA
    int x =m_x;
    int y =m_y;
    int val;
    int dir;
    srand(time(NULL));
    if (rand()>0.5)
        { dir = 1; }
    else
        {dir = -1;}
    if (rand()>0.5)
        {x = dir;}
    else
        {y=dir;}
    while (!m_grid->is_accessible(x,y))
        {
        x = m_x;
        y = m_y;
        if (rand()>0.5)
            { dir = 1; }
        else
            {dir = -1;}
        if (rand()>0.5)
            {x = x+dir;}
        else
            {y=y+dir;}
        }
    Entity::move_to_ifp(x, y );
    Entity::update();
}