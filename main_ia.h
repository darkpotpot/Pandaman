#ifndef MAIN_IA_H
#define MAIN_IA_H
#include "ia.h"
#include "explore_ia.h"
#include "follow_ia.h"
#include <map>
//class in progress
class MainIA : public IA{
public:
    MainIA(FollowIA* follow_ia, IA* explore_ia, int visibility_dist=5);
    ~MainIA();
    virtual void compute_movement(Entity *entity, Grid* grid, int& x_res, int&y_res);
 
private:
    IA* m_default_ia;
    FollowIA*  m_follow_ia;
    IA* m_active_ia;
    int m_visibility_dist;
};


#endif