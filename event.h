#ifndef EVENT_H
#define EVENT_H
#include "cell.h"

enum EventType {COLLISION};

class SimulationEvent{
public:
    SimulationEvent(EventType event_type);
    virtual EventType get_type();
    
private:
    EventType m_event_type;
};

class CollisionEvent :public SimulationEvent{
    
public:
    CollisionEvent(CellElem* element1, CellElem* element2);
    CellElem* get_element1();
    CellElem* get_element2();
private:
    EventType m_event_type;
    CellElem* m_element1;
    CellElem* m_element2;
};

#endif