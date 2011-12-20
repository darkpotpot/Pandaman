#include "entity.h"
#include "controler.h"
#include "asyncTask.h"
#include "clockObject.h"
#include "global.h"
#include "event_manager.h"
#include <list>


class SimulationTask:public AsyncTask
{
public:
    SimulationTask();
    SimulationTask(ClockObject *global_clock, Controler *controler);
    void addEntity(Entity* entity);
    ALLOC_DELETED_CHAIN(SimulationTask);
    
protected:
    virtual AsyncTask::DoneStatus do_task();
    
private:
    EventManager m_event_manager;
    double m_last_update_time;
    std::list<Entity*> m_entity_list;
    ClockObject *m_global_clock;
    double get_time();
    Controler *m_controler;

//entity list
};
