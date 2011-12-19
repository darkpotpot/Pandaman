#ifndef LEVEL_H
#define LEVEL_H

#include "grid.h"
#include "character.h"
#include "monster.h"
#include "simu.h"




class Level{

public:
    Level();
    void set_grid(Grid* grid);
    Grid* get_grid();
    /*--*/
    void set_character(MainCharacter* character);
    MainCharacter* get_character();
    /*--*/
    void set_root_node(NodePath* root_node);
    NodePath* get_root_node();
    /*--*/
    void set_simulation(SimulationTask* simu);
    SimulationTask* get_simulation();
    /*--*/
    void add_monster(Monster* m);
    std::list<Monster*>::iterator get_monster_iterator();
    std::list<Monster*>::iterator get_monster_list_end();
    
    
private:
    Grid *m_grid;
    MainCharacter *m_character;
    std::list<Monster*> m_monster;
    NodePath *m_root_node;
    SimulationTask *m_simu;
};

#endif
