#include "entity.h"
#include "asyncTask.h"
#include <list>

class SimulationTask:public AsyncTask
{
public:
    SimulationTask();
    void addEntity(Entity* entity);
    
protected:
    virtual AsyncTask::DoneStatus do_task();
    
private:
    std::list<Entity*> m_entity_list;

//entity list
};