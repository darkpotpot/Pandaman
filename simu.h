#include "entity.h"
#include "controler.h"
#include "clockObject.h"
#include "global.h"
#include "event_manager.h"
#include "simu_state.h"
#include <list>


class SimulationTask
{
public:
    SimulationTask();
    SimulationTask(ClockObject *global_clock, Controler *controler);
    void addEntity(Entity* entity);
    void removeEntity(Entity* entity);
    SimuState update(std::list<CellElem*>& to_delete_elem);
    
private:
    EventManager m_event_manager;
    double m_last_update_time;
    std::list<Entity*> m_entity_list;
    ClockObject *m_global_clock;
    double get_time();
    Controler *m_controler;

//entity list
};
