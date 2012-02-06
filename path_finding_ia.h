#ifndef PATHFINDING_IA_H
#define PATHFINDING_IA_H
#include "ia.h"
#include "point2d.h"
#include "path_finder.h"


class PathFindingIA : public IA{
public:
    PathFindingIA(PathFinder* path_finder);
    ~PathFindingIA();
    virtual void compute_movement(Entity *entity, Grid* grid, int& x_res, int&y_res);
    void set_target(Point2d point);
    bool path_empty(){return m_path.empty();}
private:
    PathFinder* m_path_finder;
    bool m_has_target;
    Point2d m_target_pos;
    list<const Cell*> m_path;
    bool is_path_up_to_date(Entity *entity);
};


#endif