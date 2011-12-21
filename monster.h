#ifndef Monster_H
#define Monster_H
#include "entity.h"
#include "ia.h"
#include "event_manager.h"

class Monster:public Entity{
public:
    Monster();
    Monster(Grid *grid);
    Monster(int x, int y, Grid *grid);
    virtual void update(EventManager& event_manager);
    virtual const CellElemType getType(){return MONSTER1;};

private:
    DirectionnalIA m_ia;
};

#endif
