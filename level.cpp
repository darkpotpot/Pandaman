#include "level.h"

Level::Level():m_grid(NULL), m_character(NULL), m_root_node(NULL), m_simu(NULL)
{}

void Level::set_grid(Grid* grid)
{m_grid = grid;}

Grid* Level::get_grid()
{return m_grid;}
/*--*/
void Level::set_character(MainCharacter* character)
{m_character = character;}

MainCharacter* Level::get_character()
{return m_character;}
/*--*/
void Level::set_root_node(NodePath* root_node)
{m_root_node = root_node;}

NodePath* Level::get_root_node()
{return m_root_node;}
/*--*/
void Level::set_simulation(SimulationTask* simu)
{m_simu = simu;}

SimulationTask* Level::get_simulation()
{return m_simu;}

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