#ifndef EVENT_H
#define EVENT_H
#include "cell.h"
#include "grid.h"
#include "event_manager.h"

class Grid;

class CollisionEvent :public SimulationEvent{
    
public:
    CollisionEvent(CellElem* element1, CellElem* element2, Grid* grid);
    EventType get_type();
    CellElem* get_element1();
    CellElem* get_element2();
private:
    EventType m_event_type;
    CellElem* m_element1;
    CellElem* m_element2;
    Grid* m_grid;
};

#endif