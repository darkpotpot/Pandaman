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