#include "simu.h"
#include "clockObject.h"
//#include "entity.h"
//#include <list>



SimulationTask::SimulationTask():m_global_clock(NULL), m_last_update_time(0.), m_controler(NULL)
{}

SimulationTask::SimulationTask(ClockObject *global_clock, Controler *controler):m_global_clock(global_clock), m_last_update_time(0.), m_controler(controler)
{}

void SimulationTask::addEntity(Entity* entity)
{m_entity_list.push_back(entity);

}

double SimulationTask::get_time()
{
    if (m_global_clock!=NULL)
        {return m_global_clock->get_frame_time();}
    else
        {return 0.;}
}

AsyncTask::DoneStatus SimulationTask::do_task()
{
    double frame_time = get_time();
    if (frame_time<m_last_update_time+UPDATE_TIME)
        {return AsyncTask::DS_cont;
        }
    m_controler->update();
    m_last_update_time = frame_time;
    std::list<Entity*>::iterator it;
    for (it=m_entity_list.begin(); it!=m_entity_list.end();it++)
        {
        (*it)->update();
        }
    return AsyncTask::DS_cont;
}
