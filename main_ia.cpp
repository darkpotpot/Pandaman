#include "detection.h"
#include "main_ia.h"
#include <iostream>
using namespace std;

MainIA::MainIA(FollowIA* follow_ia, ExploreIA* explore_ia, int visibility_dist)
: m_visibility_dist(visibility_dist), m_active_ia(NULL), m_explore_ia(explore_ia), m_follow_ia(follow_ia)
{}

MainIA::~MainIA()
{
delete m_explore_ia;
delete m_follow_ia;
}

void MainIA::compute_movement(Entity *entity, Grid* grid, int& x_res, int&y_res)
{
    int x = entity->get_x();
    int y = entity->get_y();
    bool panda_detected = false;
    int panda_x =0;
    int panda_y = 0;
    get_panda_pos_ifp(grid, x,y,panda_detected,panda_x,panda_y, m_visibility_dist);
    if (!panda_detected)
        {
        if (m_active_ia==NULL)
            {m_active_ia=m_explore_ia;}
        //once FollowIA is implemented, uncomment
        if ((m_active_ia==m_follow_ia )&&m_follow_ia->finished())
            {
                m_active_ia=m_explore_ia;
            }
        }
    else
    {
        if (m_active_ia!=m_follow_ia)
            {
            m_active_ia = m_follow_ia;
            //reinit explore_ia so that when panda lost ot doesn't prevent it from searching in surounding area if already explored before
            }
 
        m_follow_ia->set_last_known_pos(Point2d(panda_x, panda_y));
    }
    //if follow_ia active, update explore_ia with walked cases?
    return m_active_ia->compute_movement(entity, grid, x_res, y_res);
}







