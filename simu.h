#include "entity.h"
#include "asyncTask.h"
#include "clockObject.h"
#include "global.h"
#include <list>


class SimulationTask:public AsyncTask
{
public:
    SimulationTask();
    SimulationTask(ClockObject *global_clock);
    void addEntity(Entity* entity);
    
protected:
    virtual AsyncTask::DoneStatus do_task();
    
private:
    double m_last_update_time;
    std::list<Entity*> m_entity_list;
    ClockObject *m_global_clock;
    double get_time();

//entity list
};