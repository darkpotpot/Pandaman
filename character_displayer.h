#ifndef CharacterDisplayer_H
#define CharacterDisplayer_H

#include "windowFramework.h"
#include "pandaFramework.h"
#include "auto_bind.h"
#include "animControlCollection.h"
#include "cLerpNodePathInterval.h"
#include "cMetaInterval.h"
#include "displayer.h"
#include "nodePath.h"
#include <string>
#include "model_manager.h"
#include "entity_displayer.h"



class CharacterDisplayer : public EntityDisplayer
{
public:
    CharacterDisplayer(string model_name, NodePath *parentNode, ModelManager *model_manager);
    virtual int update(Displayable* entity);
private:
    AnimControlCollection m_anim_collection;
    void init_animation(ModelManager* model_manager);
    void update_play_rate(double new_update_delay);
    double m_update_delay;
    
};


#endif
