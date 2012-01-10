#include "event.h"

SimulationEvent::SimulationEvent(EventType event_type):m_event_type(event_type)
{}

EventType SimulationEvent::get_type()
{ return m_event_type; }

CollisionEvent::CollisionEvent(CellElem* element1, CellElem* element2)
:SimulationEvent(COLLISION), m_element1(element1), m_element2(element2)
{}

CellElem* CollisionEvent::get_element1()
{ return m_element1; }

CellElem* CollisionEvent::get_element2()
{ return m_element2; }
