#ifndef FOLLOW_IA_H
#define FOLLOW_IA_H
#include "ia.h"
#include "point2d.h"
#include "path_finder.h"
#include "path_finding_ia.h"
#include "entity.h"
#include "grid.h"

class FollowIA : public PathFindingIA{
public:
    FollowIA(PathFinder* path_finder);
    virtual void compute_movement(Entity *entity, Grid* grid, int& x_res, int&y_res);
    void set_last_known_pos(Point2d point);
    bool finished(){return !m_has_last_know_pos;}
private:
    bool m_has_last_know_pos;

};


#endif