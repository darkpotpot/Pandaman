#ifndef EventManager_H
#define EventManager_H
#include <list>
#include "simu_state.h"
#include "cell.h"
#include "event.h"



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

SimuState process_event(SimulationEvent* event);


#endif