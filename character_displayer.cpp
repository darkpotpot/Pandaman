#include "windowFramework.h"
#include "pandaFramework.h"
#include "character_displayer.h"
#include <string>

CharacterDisplayer::CharacterDisplayer(string model_name, WindowFramework *window, PandaFramework *framework)
:m_model_name(model_name),m_window(window), m_framework(framework)
{

     m_drawing = window->load_model(framework->get_models(), model_name);
     m_drawing.reparent_to(m_window->get_render());
     m_drawing.set_scale(0.025, 0.025, 0.025);
}


int CharacterDisplayer::update(Displayable* entity)
{
    float x = (float)(10*entity->get_x());
    float y = (float)(10*entity->get_y());
    float drawing_x = m_drawing.get_x();
    float drawing_y = m_drawing.get_y();
    if (x==drawing_x&&y==drawing_y)
        {return 0;
            }
    m_drawing.set_pos( x, y, 0.);
    float head =m_drawing.get_hpr().get_x();
    if (drawing_x>x)
        {head=-90.;}
    if (drawing_x<x)
        {head=90.;}
    if (drawing_y>y)
        {head=0.;}
    if (drawing_y<y)
        {head=180.;}
    m_drawing.set_hpr( head,0.,0.);
    return 0;
}