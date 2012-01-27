#include "windowFramework.h"
#include "pandaFramework.h"
#include "auto_bind.h"


#include "cLerpNodePathInterval.h"
#include "cMetaInterval.h"

#include "animControlCollection.h"
#include "animControl.h"
#include "character_displayer.h"
#include "character.h"
#include "entity_displayer.h"
#include "global.h"
#include <string>
#include <cmath>

extern int CASE_RATIO;
extern double UPDATE_TIME;

CharacterDisplayer::CharacterDisplayer(string model_name, NodePath *parentNode, ModelManager* model_manager)
:EntityDisplayer( model_name, parentNode, model_manager), m_update_delay(UPDATE_TIME)
{

    //m_drawing = model_manager->loadModel(model_name);
    //m_drawing.reparent_to(*mParentNode);
    //m_drawing.set_scale(0.008, 0.008, 0.008);
    //m_PosPace = new CMetaInterval("pandaPace");
    init_animation(model_manager);
}

void CharacterDisplayer::init_animation(ModelManager* model_manager)
{ 
    model_manager->loadModel("panda-walk4").reparent_to(m_drawing);
    auto_bind(m_drawing.node(), m_anim_collection);
    m_anim_collection.loop("panda_soft", true);
    AnimControl *anim_control = m_anim_collection.find_anim("panda_walk_character");
    int frame_rate = anim_control->get_frame_rate();
    int num_frame  = anim_control->get_num_frames();
    float playrate = num_frame/(m_update_delay*frame_rate);
    anim_control->set_play_rate(playrate);
}

void CharacterDisplayer::update_play_rate(double new_update_delay){
    std::cout<<"updating delay time "<<new_update_delay<<endl;
    m_update_delay = new_update_delay;
    AnimControl *anim_control = m_anim_collection.find_anim("panda_walk_character");
    int frame_rate = anim_control->get_frame_rate();
    int num_frame  = anim_control->get_num_frames();
    float playrate = num_frame/(m_update_delay*frame_rate);
    anim_control->set_play_rate(playrate);
}

int CharacterDisplayer::update(Displayable* entity)
{
    float x = (float)(0.5*CASE_RATIO+CASE_RATIO*entity->get_x());
    float y = (float)(0.5*CASE_RATIO+CASE_RATIO*entity->get_y());
    float drawing_x = m_drawing.get_x();
    float drawing_y = m_drawing.get_y();
    //TODO GROM : change function prototype to take MainCharacter and avoid dynamic cast
    MainCharacter* main_character = dynamic_cast<MainCharacter*>(entity);
    double character_update_delay = main_character->get_update_delay();
    if (character_update_delay!=m_update_delay)
    {
        update_play_rate(character_update_delay);
    }
    if (main_character->hasState(DRUNK))
    {
        m_drawing.set_color(0,0.5,0,1);
    }
    else if (main_character->hasState(INVINCIBLE))
    {
        m_drawing.set_color(0.5,0,0,1);
    }
    else if (main_character->hasState(FAST))
    {
        m_drawing.set_color(0,0,0.5,1);
    }
    else
    {
        m_drawing.set_color_off();
    }
    if (max(abs(x-drawing_x),abs(y-drawing_y)) <0.01*CASE_RATIO)
        {
            m_anim_collection.pose("panda_walk_character", m_anim_collection.get_frame());
            return 0;
        }
    if (!m_anim_collection.is_playing())
        {
          m_anim_collection.loop_all(false); 
        }
    update_pos(LPoint3f(x, y, m_altitude), m_update_delay);    
    return 0;
}

