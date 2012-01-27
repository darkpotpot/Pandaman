#include "level.h"
#include "cell.h"

Level::Level(const char* pMapname):m_character(NULL), m_root_node(NodePath(pMapname))
{
    LevelLoader levelLoader = LevelLoader(pMapname);
    m_grid = new Grid(levelLoader.getWidth(), levelLoader.getHeight());
    fillMapCells(levelLoader.getLayer(string("World")), levelLoader);
    fillMapCells(levelLoader.getLayer(string("Character")), levelLoader);
	fillMapCells(levelLoader.getLayer(string("Objects")), levelLoader);
    assert ((m_character != NULL));
}

Level::~Level(){
    delete m_grid;
}

void Level::fillMapCells(TiXmlElement* worldElem, LevelLoader& levelLoader){
    assert(worldElem);
    for (int i=m_grid->getHeight() - 1; i > -1; i--){ //panda is not sorted in the same order than the map
        for (int j=0; j < m_grid->getWidth(); j++){
			CellInfo cell = levelLoader.getCellElem(string(worldElem->Attribute("gid")));
			switch(cell.type){
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
                case FOOD:
                    add_food(new Food(j, i), j, i);
                    break;
				case BONUS:
					addBonus(static_cast<CharStateType>(cell.additionalInfo), 20, j, i);
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

void Level::add_food(Food* food, int x, int y)
{
    m_grid->addElem(x,y,food);
}

void Level::addBonus(CharStateType stateType, int nbTurn, int x, int y)
{
 m_grid->addElem(x,y,new Bonus(x, y, nbTurn, stateType));
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


//TODO GROM: refactor two following methods in one
void Level::delete_food(Food* food)
{
    m_grid->removeElem(food->get_x(), food->get_y(), dynamic_cast<CellElem*>(food));
    delete food->getDisplayer();
    food->set_displayer(NULL);
    delete food;
}

void Level::delete_bonus(Bonus* bonus)
{
    m_grid->removeElem(bonus->get_x(), bonus->get_y(), dynamic_cast<CellElem*>(bonus));
    delete bonus->getDisplayer();
    bonus->set_displayer(NULL);
    delete bonus;
}


void Level::delete_monster(Monster* m)
{
    m_monster.remove(m);
    m_grid->removeElem(m->get_x(), m->get_y(), dynamic_cast<CellElem*>(m));
    delete m->getDisplayer();
    m->set_displayer(NULL);
    delete m;

}