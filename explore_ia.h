#ifndef EXPLORE_IA_H
#define EXPLORE_IA_H
#include "ia.h"
#include <map>

class Point2d{

public:
    Point2d():m_x(0), m_y(0){}
    Point2d(int x, int y):m_x(x), m_y(y){}
    int get_x() const {return m_x;}
    int get_y()const {return m_y;}
    
private:
    int m_x;
    int m_y;
};

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

Point2d operator+(const Point2d& p1, const Point2d& p2);

//necessary because in order to be used as key in map...need to be comparable...
bool operator<(const Point2d& p1, const Point2d& p2);

#endif