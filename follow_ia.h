#ifndef FOLLOW_IA_H
#define FOLLOW_IA_H
#include "ia.h"
#include "point2d.h"
#include <map>
#include "path_finder.h"
#include "math.h"
//class in progress

class PathFinder : public AbstractPathFinder<Cell>{
public:
    PathFinder(Grid* grid) : m_grid(grid), AbstractPathFinder<Cell>(){}
    // --
    virtual float dist_between(const Cell*const c1, const Cell*const c2)
    {
        int x_dist = c1->get_x()-c1->get_x();
        int y_dist = c1->get_y()-c1->get_y();
        return sqrt((float)(x_dist*x_dist+y_dist*y_dist));
    }
    // --
    virtual list<const Cell*> get_neighbors(const Cell* c)
    {
        list<const Cell*> case_list;
        int x = c->get_x();
        int y = c->get_y();
        if(x>0&&m_grid->is_accessible(x-1, y))
        { case_list.push_back(m_grid->getCell(x-1, y)); }
        if(x<m_grid->getWidth()&&m_grid->is_accessible(x+1, y))
        { case_list.push_back(m_grid->getCell(x+1, y)); }
        if(y>0&&m_grid->is_accessible(x, y-1))
        { case_list.push_back(m_grid->getCell(x, y-1)); }
        if(y<m_grid->getHeight()&&m_grid->is_accessible(x, y+1))
        { case_list.push_back(m_grid->getCell(x, y+1)); }
        return case_list;
    }
private:
    Grid* m_grid;
};

class FollowIA : public IA{
public:
    FollowIA(PathFinder* path_finder);
    ~FollowIA();
    virtual void compute_movement(Entity *entity, Grid* grid, int& x_res, int&y_res);
    void set_last_known_pos(Point2d point);
    bool finished(){return !m_has_last_know_pos;}
private:
    PathFinder* m_path_finder;
    bool m_has_last_know_pos;
    Point2d m_last_known_pos;
    list<const Cell*> m_path;
    bool is_path_up_to_date(Entity *entity);
};


#endif