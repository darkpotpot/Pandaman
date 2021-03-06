#ifndef EntityDisplayer_H
#define EntityDisplayer_H

#include "windowFramework.h"
#include "pandaFramework.h"
#include "cLerpNodePathInterval.h"
#include "cMetaInterval.h"
#include "displayer.h"
#include "nodePath.h"
#include <string>
#include "model_manager.h"
#include "global.h"
#include "color_modifier.h"


class EntityDisplayer : public Displayer
{
public:
    EntityDisplayer(string model_name, NodePath *parentNode, ModelManager *model_manager, Color color =NO_COLOR);
    EntityDisplayer(string model_name, NodePath *parentNode, ModelManager *model_manager, float altitude, LPoint3f scale, Color color =NO_COLOR);
    virtual ~EntityDisplayer();
    virtual int update(Displayable* entity);
	NodePath getDrawing() {return m_drawing;};
protected:
    static int idx;
    float m_altitude;
    void update_pos(LPoint3f new_pos, double update_delay=UPDATE_TIME);
    NodePath m_drawing;
private:
    NodePath *mParentNode;
    string m_model_name;
    PT(CMetaInterval) m_PosPace;
    double get_new_head(LPoint3f old_pos, LPoint3f new_pos);
    void clear_lerp_ifn();
    void add_pos_lerp(LPoint3f start_pos, LPoint3f end_pos, double lenght);
    void add_hpr_lerp(LPoint3f start_hpr, LPoint3f end_pos, double lenght);
    
};


#endif