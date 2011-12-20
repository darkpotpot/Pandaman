#include "level.h"
#include "monster.h"

Level::Level(const char* pMapname)
{
    m_grid = Grid();
    m_grid.loadMap(pMapname);
    m_character = MainCharacter(1, 1, &m_grid);
    m_root_node = NodePath(pMapname);
    addEntity(&m_character);
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

void Level::addEntity(Entity* entity)
{
    int x=entity->get_x();
    int y=entity->get_y();
    m_grid.addElem(x,y,entity);
}

std::list<Monster*>::iterator Level::get_monster_iterator()
{ return m_monster.begin(); }


std::list<Monster*>::iterator Level::get_monster_list_end()
{ return m_monster.end(); }

void Level::add_monster(Monster* m)
{
    m_monster.push_back(m);
    addEntity(m);
}

