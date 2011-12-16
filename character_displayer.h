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



class CharacterDisplayer : public Displayer
{
public:
    CharacterDisplayer(string model_name, NodePath *parentNode, ModelManager *model_manager);
    virtual int update(Displayable* entity);
private:
    NodePath m_drawing;
    NodePath *mParentNode;
    string m_model_name;
    AnimControlCollection m_anim_collection;
    PT(CMetaInterval) m_PosPace;
    void update_pos(LPoint3f new_pos);
    double get_new_head(LPoint3f old_pos, LPoint3f new_pos);
    void clear_lerp_ifn();
    void add_pos_lerp(LPoint3f start_pos, LPoint3f end_pos, double lenght);
    void add_hpr_lerp(LPoint3f start_hpr, LPoint3f end_pos, double lenght);
    
};


#endif
