#include "monster.h"
#include <stdlib.h>
#include <time.h>
#include "main_ia.h"
#include <iostream>

using namespace std;
Monster::Monster():Entity()
{}

Monster::Monster(Grid *grid):
    m_ia(new MainIA(new FollowIA(new PathFinder(grid)),new ExploreIA())), 
    Entity(grid)
{
}

Monster::Monster(int x, int y, Grid *grid):
    m_ia(new MainIA(new FollowIA(new PathFinder(grid)),new ExploreIA())), 
    Entity(x, y, grid)
{}

Monster::~Monster()
{
delete m_ia;
}

void Monster::update(EventManager& event_manager)
{
    int x;
    int y;
    m_ia->compute_movement(this, m_grid, x, y);
    Entity::move_to_ifp(x, y, event_manager);
    Entity::update(event_manager);
}