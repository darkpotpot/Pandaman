#ifndef Monster_H
#define Monster_H
#include "entity.h"

#include "explore_ia.h"
#include "main_ia.h"
#include "event_manager.h"

enum MonsterIA {ROAMING, GUARDING};

class Monster:public Entity{
public:
    Monster();
    Monster(MainIA* ia, Grid *grid);
    Monster(int x, int y, MainIA* ia, Grid *grid);
    virtual ~Monster();
    virtual void update(EventManager& event_manager);
    virtual const CellElemType getType(){return MONSTER1;};

private:
    MainIA* m_ia;
};

Monster * create_monster(int x, int y, Grid *grid, MonsterIA monster_ia);


#endif
