#include "event.h"



CollisionEvent::CollisionEvent(CellElem* element1, CellElem* element2, Grid* grid)
:SimulationEvent(COLLISION), m_element1(element1), m_element2(element2), m_grid(grid)
{}

CellElem* CollisionEvent::get_element1()
{ return m_element1; }

CellElem* CollisionEvent::get_element2()
{ return m_element2; }