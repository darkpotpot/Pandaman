#include "windowFramework.h"
#include "pandaFramework.h"


#include "cLerpNodePathInterval.h"
#include "cMetaInterval.h"

#include "character_displayer.h"

#include <string>
#include <cmath>
#include <stdlib.h>

#include <sstream>  

template<typename T>
std::string to_string( const T & Value )
{
    // utiliser un flux de sortie pour créer la chaîne
    std::ostringstream oss;
    // écrire la valeur dans le flux
    oss << Value;
    // renvoyer une string
    return oss.str();
}



extern int CASE_RATIO;
extern double UPDATE_TIME;

int EntityDisplayer::idx=0;

EntityDisplayer::EntityDisplayer(string model_name, NodePath *parentNode, ModelManager* model_manager)
:m_model_name(model_name),mParentNode(parentNode), m_PosPace(NULL), m_altitude(0.)
{
    EntityDisplayer::idx = EntityDisplayer::idx+1;
	m_drawing = NodePath(model_name);
    NodePath drawing = model_manager->loadModel(model_name);
	drawing.set_scale(0.008, 0.008, 0.008);
	drawing.reparent_to(m_drawing);
    m_drawing.reparent_to(*mParentNode);
    m_PosPace = new CMetaInterval(string("pandaPace")+to_string(EntityDisplayer::idx));
}

EntityDisplayer::EntityDisplayer(string model_name, NodePath *parentNode, ModelManager* model_manager, float altitude, LPoint3f scale)
:m_model_name(model_name),mParentNode(parentNode), m_PosPace(NULL), m_altitude(altitude)
{
    EntityDisplayer::idx = EntityDisplayer::idx+1;
    m_drawing = model_manager->loadModel(model_name);
    m_drawing.reparent_to(*mParentNode);
    m_drawing.set_scale(scale);
    m_PosPace = new CMetaInterval("pandaPace"+to_string(EntityDisplayer::idx));
}

EntityDisplayer::~EntityDisplayer()
{
m_drawing.remove_node();

}

int EntityDisplayer::update(Displayable* entity)
{
    float x = (float)(0.5*CASE_RATIO+CASE_RATIO*entity->get_x());
    float y = (float)(0.5*CASE_RATIO+CASE_RATIO*entity->get_y());
    float drawing_x = m_drawing.get_x();
    float drawing_y = m_drawing.get_y();
    if (max(abs(x-drawing_x),abs(y-drawing_y)) <0.01*CASE_RATIO)
        {
            return 0;
        }
    update_pos(LPoint3f(x, y, m_altitude));    
    return 0;
}

void EntityDisplayer::update_pos(LPoint3f new_pos, double update_delay)
{
    LPoint3f old_pos = m_drawing.get_pos();
    clear_lerp_ifn();
    LPoint3f old_hpr = m_drawing.get_hpr();
    double head = get_new_head(old_pos, new_pos);
    LPoint3f new_hpr = LPoint3f(head, 0.,0.);
    if (old_hpr.get_x()-new_hpr.get_x()>180)
        {old_hpr = LPoint3f(old_hpr.get_x()-360.,0.,0.);
        }
    if (old_hpr.get_x()-new_hpr.get_x()<-180)
        {old_hpr = LPoint3f(old_hpr.get_x()+360.,0.,0.);
        }
    double pos_update_time = update_delay;
    if (old_hpr!=new_hpr)
    {
        add_hpr_lerp(old_hpr, new_hpr, pos_update_time*0.50);
        pos_update_time = pos_update_time*0.5;
    }
    add_pos_lerp(old_pos, new_pos, pos_update_time);
    m_PosPace->start(0., update_delay, 1.);
 }   
 
void EntityDisplayer::clear_lerp_ifn()
{
    if (m_PosPace!=NULL)
    {
        m_PosPace->finish();
        m_PosPace->clear_intervals();
    } 
}

void EntityDisplayer::add_pos_lerp(LPoint3f start_pos, LPoint3f end_pos, double lenght)
{
    PT(CLerpNodePathInterval) posInterval =new CLerpNodePathInterval("pandaPosInterval1",
                                             lenght, CLerpInterval::BT_no_blend,//CLerpInterval::BT_ease_in_out,
                                             true, false, m_drawing, NULL);
    posInterval->set_start_pos(start_pos);
    posInterval->set_end_pos(end_pos);
    m_PosPace->add_c_interval(posInterval, 0, CMetaInterval::RS_previous_end);
}

void EntityDisplayer::add_hpr_lerp(LPoint3f start_hpr, LPoint3f end_hpr, double lenght)
{
    PT(CLerpNodePathInterval) hprInterval =new CLerpNodePathInterval("pandaPosInterval1",
                                             lenght, CLerpInterval::BT_no_blend,//CLerpInterval::BT_ease_in_out,
                                             true, false, m_drawing, NULL);            
    hprInterval->set_start_hpr(start_hpr);
    hprInterval->set_end_hpr(end_hpr);
    m_PosPace->add_c_interval(hprInterval, 0, CMetaInterval::RS_previous_end);
}
 
double EntityDisplayer::get_new_head(LPoint3f old_pos, LPoint3f new_pos)
{
    LVector3f dir = new_pos-old_pos;
    float diff_x = dir.get_x();
    float diff_y = dir.get_y();
    float head = m_drawing.get_hpr().get_x();
    if (!(diff_x==0&&diff_y==0))
    {
        if (abs(diff_x)>abs(diff_y))
        {
            if (diff_x>0)
                {head=90.;}
            else
                {head=-90.;}
        }
        else
        {
            if (diff_y>0)
                {head=180.;}
            else
                {head=0.;}
        }
    }
    return head;
}
