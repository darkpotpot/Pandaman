#include "event_manager.h"

EventManager::EventManager()
{}

void EventManager::addEvent(SimulationEvent* event)
{ m_event_list.push_back(event); }

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
		{ delete &(*it); }
    m_event_list.clear();
    
}


SimuState character_monster_collision(CellElem* character, CellElem* monster)
{
return RESTART;
}

SimuState process_collision_event(CollisionEvent* event)
{
	CellElem* elem1 = event->get_element1();
	CellElem* elem2 = event->get_element2();
	if (elem1->getType()==CHARACTER && elem2->getType()==MONSTER1)
		{return character_monster_collision(elem1, elem2);}
	else if (elem2->getType()==MONSTER1 && elem1->getType()==CHARACTER)
		{return character_monster_collision(elem2, elem1);}
	return CONTINUE;

}

SimuState process_event(SimulationEvent* event)
{
	EventType event_type = event->get_type();
	if (event_type==COLLISION)
	{
		return process_collision_event(dynamic_cast<CollisionEvent*>(event));
	}
	return CONTINUE;

}

