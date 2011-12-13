#include "displayable.h"
#include <iostream>

Displayable::Displayable(): m_displayer(NULL)
{
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

