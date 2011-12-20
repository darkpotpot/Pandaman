#ifndef LEVEL_H
#define LEVEL_H

#include "grid.h"
#include "character.h"
#include "monster.h"
#include "nodePath.h"
#include "tinyxml/tinyxml.h"


class Level{

public:
    Level(const char* pMapname);
    ~Level();
    Grid* get_grid();
    MainCharacter* get_character();
    NodePath* get_root_node();
    void addEntity(Entity* entity);
    void add_monster(Monster* m);
    std::list<Monster*>::iterator get_monster_iterator();
    std::list<Monster*>::iterator get_monster_list_end();


private:
    Grid* m_grid;
    std::list<Monster*> m_monster;
    MainCharacter* m_character;
    NodePath m_root_node; //not very clean, the object knows it's a NodePath, todo:inherits from displayable and do the same but a bit of pain in the ass for a small test project.
    void loadMap(TiXmlHandle layerHandle);
};

#endif
