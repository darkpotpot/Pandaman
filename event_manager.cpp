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


SimuState character_monster_collision(CellElem* character, CellElem* monster, std::list<CellElem*>& to_delete_list)
{
return RESTART;
}

SimuState character_food_collision(CellElem* character, CellElem* food, std::list<CellElem*>& to_delete_list)
{
to_delete_list.push_back(food);
return CONTINUE;
}

SimuState process_collision_event(CollisionEvent* event, std::list<CellElem*>& to_delete_list)
{
	CellElem* elem1 = event->get_element1();
	CellElem* elem2 = event->get_element2();
	if (elem1->getType()==CHARACTER && elem2->getType()==MONSTER1)
		{return character_monster_collision(elem1, elem2, to_delete_list);}
	else if (elem1->getType()==MONSTER1 && elem2->getType()==CHARACTER)
		{return character_monster_collision(elem2, elem1, to_delete_list);}
	else if (elem1->getType()==CHARACTER && elem2->getType()==FOOD)
		{return character_food_collision(elem1, elem2, to_delete_list);}
	else if (elem2->getType()==FOOD && elem1->getType()==CHARACTER)
		{return character_food_collision(elem2, elem1, to_delete_list);}
	return CONTINUE;

}

SimuState process_event(SimulationEvent* event, std::list<CellElem*>& to_delete_list)
{
	EventType event_type = event->get_type();
	if (event_type==COLLISION)
	{
		return process_collision_event(dynamic_cast<CollisionEvent*>(event), to_delete_list);
	}
	return CONTINUE;

}

