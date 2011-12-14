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



class CharacterDisplayer : public Displayer
{
public:
    CharacterDisplayer(string model_name, WindowFramework *window, PandaFramework *framework);
    virtual int update(Displayable* entity);
private:
    NodePath m_drawing;
    WindowFramework *m_window;
    PandaFramework *m_framework;
    string m_model_name;
    AnimControlCollection m_anim_collection;
    PT(CMetaInterval) m_PosPace;
    void update_pos(LPoint3f new_pos);
    
    
};


#endif