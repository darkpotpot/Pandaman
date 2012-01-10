#include "displayable.h"
#include <iostream>

Displayable::Displayable(): m_displayer(NULL)
{
}

Displayable::~Displayable()
{
    delete m_displayer;
}

int Displayable::get_x()
{
    return 0;
    }
int Displayable::get_y(){
    return 0;
    }
void Displayable::set_displayer(Displayer * displayer)
{ m_displayer = displayer; }

Displayer* Displayable::getDisplayer(){
    return m_displayer;
}
