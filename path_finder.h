#ifndef PATHFINDER_H
#define PATHFINDER_H
#include "point2d.h"
#include "abstract_path_finder.h"
#include "grid.h"
#include "math.h"

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

#endif