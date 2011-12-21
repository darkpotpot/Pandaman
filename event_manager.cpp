#include "event_manager.h"

SimulationEvent::SimulationEvent(EventType event_type):m_event_type(event_type)
{}

EventType SimulationEvent::get_type()
{ return m_event_type; }

EventManager::EventManager()
{}

void EventManager::addEvent(SimulationEvent* event)
{
    m_event_list.push_back(event);
}

SimulationEvent* EventManager::popFirstEvent()
{
    SimulationEvent * event = m_event_list.front();
    m_event_list.pop_front();
    return event;
}

SimulationEvent* EventManager::popLastEvent()
{
    SimulationEvent * event = m_event_list.back();
    m_event_list.pop_back();
    return event;
}

bool EventManager::empty()
{ return m_event_list.empty(); }

void EventManager::cleanEvents()
{
    std::list<SimulationEvent*>::iterator it;
    for (it = m_event_list.begin();it !=m_event_list.end();it++)
    {
        delete &(*it);
    }
    m_event_list.clear();
    
}
