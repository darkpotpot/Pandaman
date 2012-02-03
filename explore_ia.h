#ifndef EXPLORE_IA_H
#define EXPLORE_IA_H
#include "ia.h"
#include "point2d.h"
#include <map>

class ExploreIA : public IA{
public:
    ExploreIA();
    ~ExploreIA();
    virtual void compute_movement(Entity *entity, Grid* grid, int& x_res, int&y_res);
 
private:
    void get_accessible_neightboors(Grid* grid, Point2d& current_pos, list<Point2d>& res_list);
    list<Point2d>& get_accessible_direction();
    static list<Point2d> m_accessible_directions;
    std::map<Point2d, int> m_exploration_map;
};


#endif