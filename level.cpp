#include "level.h"

Level::Level(const char* pMapname)
{
    m_grid = Grid();
    m_grid.loadMap(pMapname);
    m_character = MainCharacter(1, 1, &m_grid);
    m_root_node = NodePath(pMapname);
    addEntity(&m_character);
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

