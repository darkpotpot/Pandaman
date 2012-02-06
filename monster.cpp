#include "monster.h"
#include <stdlib.h>
#include <time.h>
#include "main_ia.h"
#include "ia.h"
#include "point2d.h"
#include <iostream>

using namespace std;
Monster::Monster():Entity()
{}

Monster::Monster(MainIA* ia, Grid *grid):
    m_ia(ia), 
    Entity(grid)
{
}

Monster::Monster(int x, int y, MainIA* ia, Grid *grid):
    m_ia(ia), 
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

Monster * create_monster(int x, int y, Grid *grid, MonsterIA monster_ia)
{
    IA * default_ia = NULL;
    FollowIA * follow_ia = new FollowIA(new PathFinder(grid));
    if (monster_ia==ROAMING)
    {
        ExploreIA* explore_ia = new ExploreIA();
        default_ia = explore_ia;
    }
    else if (monster_ia==GUARDING)
    {
        PathFindingIA* guard_ia = new PathFindingIA(new PathFinder(grid));
        guard_ia->set_target(Point2d(x,y));
        default_ia = guard_ia;
    }
    MainIA * main_ia = new MainIA(follow_ia, default_ia);
    return new Monster(x,y,main_ia, grid);
}