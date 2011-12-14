#include "windowFramework.h"
#include "pandaFramework.h"
#include "auto_bind.h"


#include "cLerpNodePathInterval.h"
#include "cMetaInterval.h"

#include "animControlCollection.h"
#include "animControl.h"
#include "character_displayer.h"
#include "global.h"
#include <string>
#include <cmath>

extern int CASE_RATIO;
extern double UPDATE_TIME;

CharacterDisplayer::CharacterDisplayer(string model_name, WindowFramework *window, PandaFramework *framework)
:m_model_name(model_name),m_window(window), m_framework(framework), m_PosPace(NULL)
{

    m_drawing = window->load_model(framework->get_models(), model_name);
    m_drawing.reparent_to(m_window->get_render());
    m_drawing.set_scale(0.008, 0.008, 0.008);
    window->load_model(m_drawing, "panda-walk4");
    auto_bind(m_drawing.node(), m_anim_collection);
    m_anim_collection.loop("panda_soft", true);
    //m_anim_collection.loop_all(true);
    AnimControl *anim_control = m_anim_collection.find_anim("panda_walk_character");

    int frame_rate = anim_control->get_frame_rate();
    int num_frame = anim_control->get_num_frames();
    float playrate = num_frame/(UPDATE_TIME*frame_rate);
    anim_control->set_play_rate(playrate);
    //cout<<"frame_rate= "<<frame_rate<<endl;
    //cout<<"num_frame= "<<num_frame<<endl;
    //cout<<"play_rate= "<<anim_control->get_play_rate()<<endl;

    //anim_collection.pose("panda_soft", 5);
    //cout<<m_anim_collection.which_anim_playing()<<endl;
    m_PosPace = new CMetaInterval("pandaPace");
}

float max(float x, float y)
{if(x>y) {return x;}
 else    {return y;}}

int CharacterDisplayer::update(Displayable* entity)
{
    float x = (float)(0.5*CASE_RATIO+CASE_RATIO*entity->get_x());
    float y = (float)(0.5*CASE_RATIO+CASE_RATIO*entity->get_y());
    float drawing_x = m_drawing.get_x();
    float drawing_y = m_drawing.get_y();
    if (max(abs(x-drawing_x),abs(y-drawing_y)) <0.01*CASE_RATIO)
        {
            m_anim_collection.pose("panda_walk_character", m_anim_collection.get_frame());
            return 0;
        }
    if (!m_anim_collection.is_playing())
        {
          m_anim_collection.loop_all(false); 
          //m_anim_collection.play("panda_walk_character"); 
        }
    update_pos(LPoint3f(x, y, 0));    
    return 0;
}

void CharacterDisplayer::update_pos(LPoint3f new_pos)
{
    LPoint3f old_pos = m_drawing.get_pos();
    clear_lerp_ifn();
    LPoint3f old_hpr=m_drawing.get_hpr();
    double head = get_new_head(old_pos, new_pos);


    LPoint3f new_hpr = LPoint3f(head, 0.,0.);
    if (old_hpr.get_x()-new_hpr.get_x()>180)
        {old_hpr = LPoint3f(old_hpr.get_x()-360.,0.,0.);
        }
    if (old_hpr.get_x()-new_hpr.get_x()<-180)
        {old_hpr = LPoint3f(old_hpr.get_x()+360.,0.,0.);
        }

    double pos_update_time = UPDATE_TIME;
    if (old_hpr!=new_hpr)
    {
        add_hpr_lerp(old_hpr, new_hpr, pos_update_time*0.50);
        pos_update_time = pos_update_time*0.5;
    }
    add_pos_lerp(old_pos, new_pos, pos_update_time);
    m_PosPace->start(0., UPDATE_TIME, 1.);

 }   
 
void CharacterDisplayer::clear_lerp_ifn()
{
    if (m_PosPace!=NULL)
    {
        m_PosPace->finish();
        m_PosPace->clear_intervals();
    } 
}

void CharacterDisplayer::add_pos_lerp(LPoint3f start_pos, LPoint3f end_pos, double lenght)
{
    PT(CLerpNodePathInterval) posInterval =new CLerpNodePathInterval("pandaPosInterval1",
                                             lenght, CLerpInterval::BT_no_blend,//CLerpInterval::BT_ease_in_out,
                                             true, false, m_drawing, NodePath());
    posInterval->set_start_pos(start_pos);
    posInterval->set_end_pos(end_pos);
    m_PosPace->add_c_interval(posInterval, 0, CMetaInterval::RS_previous_end);
}

void CharacterDisplayer::add_hpr_lerp(LPoint3f start_hpr, LPoint3f end_hpr, double lenght)
{
    PT(CLerpNodePathInterval) hprInterval =new CLerpNodePathInterval("pandaPosInterval1",
                                             lenght, CLerpInterval::BT_no_blend,//CLerpInterval::BT_ease_in_out,
                                             true, false, m_drawing, NodePath());            
    hprInterval->set_start_hpr(start_hpr);
    hprInterval->set_end_hpr(end_hpr);
    m_PosPace->add_c_interval(hprInterval, 0, CMetaInterval::RS_previous_end);
}
 
double CharacterDisplayer::get_new_head(LPoint3f old_pos, LPoint3f new_pos)
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