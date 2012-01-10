#include "simu.h"
#include "clockObject.h"
#include "event.h"
#include "simu_state.h"



SimulationTask::SimulationTask():m_global_clock(NULL), m_last_update_time(0.), m_controler(NULL)
{}

SimulationTask::SimulationTask(ClockObject *global_clock, Controler *controler):m_global_clock(global_clock), m_last_update_time(0.), m_controler(controler)
{}

void SimulationTask::addEntity(Entity* entity)
{m_entity_list.push_back(entity);}

void SimulationTask::removeEntity(Entity* entity)
{m_entity_list.remove(entity);}

double SimulationTask::get_time()
{
    if (m_global_clock!=NULL)
        {return m_global_clock->get_frame_time();}
    else
        {return 0.;}
}

SimuState SimulationTask::update(std::list<CellElem*>& to_delete_elem)
{
    double frame_time = get_time();
    if (frame_time<m_last_update_time+UPDATE_TIME)
        {return CONTINUE;
        }
    m_controler->update();
    m_last_update_time = frame_time;
    std::list<Entity*>::iterator it;
    for (it=m_entity_list.begin(); it!=m_entity_list.end();it++)
        {
        (*it)->update(m_event_manager);
        }
    
    //
	SimuState simuState(CONTINUE);
    SimulationEvent * event;
    while (!m_event_manager.empty())
    {
        event = m_event_manager.popFirstEvent();
		simuState = process_event(event, to_delete_elem);
		if (simuState!=CONTINUE)
			{return simuState;}
    }
 
    return simuState;
}
