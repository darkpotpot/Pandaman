#ifndef EventManager_H
#define EventManager_H
#include <list>

enum EventType {COLLISION};

class SimulationEvent{
public:
    SimulationEvent(EventType event_type);
    EventType get_type();
    
private:
    EventType m_event_type;
};

class EventManager{
    
public:
    EventManager();
    void addEvent(SimulationEvent* event);
    SimulationEvent* popFirstEvent();
    SimulationEvent* popLastEvent();
    bool empty();
    void cleanEvents();
    
private:
    std::list<SimulationEvent*> m_event_list;
};

#endif