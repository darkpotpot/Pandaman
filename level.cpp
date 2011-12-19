#include "level.h"
#include "monster.h"

Level::Level(const char* pMapname)
{
    m_grid = Grid();
    m_grid.loadMap(pMapname);
    m_character = MainCharacter(1, 1, &m_grid);
    m_root_node = NodePath(pMapname);

    add_monster(new Monster(1,2,&m_grid));
    add_monster(new Monster(2,2,&m_grid));
}

Grid* Level::get_grid()
{return &m_grid;}
/*--*/
MainCharacter* Level::get_character()
{return &m_character;}
/*--*/
NodePath* Level::get_root_node()
{return &m_root_node;}

void Level::add_monster(Monster* m)
{
m_monster.push_back(m);
}

std::list<Monster*>::iterator Level::get_monster_iterator()
{
    std::list<Monster*>::iterator it = m_monster.begin();
    return it;
}

std::list<Monster*>::iterator Level::get_monster_list_end()
{
    std::list<Monster*>::iterator it = m_monster.end();
    return it;
}
