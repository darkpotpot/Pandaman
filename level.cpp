#include "level.h"
#include "monster.h"
#include "cell.h"

Level::Level(const char* pMapname):m_character(NULL), m_root_node(NodePath(pMapname))
{
    LevelLoader levelLoader = LevelLoader(pMapname);
    m_grid = new Grid(levelLoader.getWidth(), levelLoader.getHeight());
    fillMapCells(levelLoader.getLayer(string("World")), levelLoader);
    fillMapCells(levelLoader.getLayer(string("Character")), levelLoader);
    assert ((m_character != NULL));
}

Level::~Level(){
    delete m_grid;
}

void Level::fillMapCells(TiXmlElement* worldElem, LevelLoader& levelLoader){
    assert(worldElem);
    for (int i=m_grid->getHeight() - 1; i > -1; i--){ //panda is not sorted in the same order than the map
        for (int j=0; j < m_grid->getWidth(); j++){
            switch(levelLoader.getCellElem(string(worldElem->Attribute("gid")))){
                case WALL:
                    m_grid->addElem(j, i, new Wall());
                    break;
                case CHARACTER:
                    assert(m_character == NULL);
                    m_character = new MainCharacter(j, i, m_grid);
                    addEntity(m_character);
                    break;
                case MONSTER1:
                    add_monster(new Monster(j, i, m_grid));
                    break;
            }
            worldElem = worldElem->NextSiblingElement();
        }
    }
}

Grid* Level::get_grid()
{return m_grid;}
/*--*/
MainCharacter* Level::get_character()
{return m_character;}
/*--*/
NodePath* Level::get_root_node()
{return &m_root_node;}

void Level::addEntity(Entity* entity)
{
    int x=entity->get_x();
    int y=entity->get_y();
    m_grid->addElem(x,y,entity);
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

