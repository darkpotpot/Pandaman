#include "simu.h"
//#include "entity.h"
//#include <list>

SimulationTask::SimulationTask()
{}

void SimulationTask::addEntity(Entity* entity)
{m_entity_list.push_back(entity);
}

AsyncTask::DoneStatus SimulationTask::do_task()
{
    std::list<Entity*>::iterator it;
    for (it=m_entity_list.begin(); it!=m_entity_list.end();it++)
        {
        (*it)->update();
        }
    return AsyncTask::DS_cont;
}
