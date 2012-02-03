#ifndef POINT2D_H
#define POINT2D_H
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


Point2d operator+(const Point2d& p1, const Point2d& p2);

//necessary because in order to be used as key in map...need to be comparable...
bool operator<(const Point2d& p1, const Point2d& p2);
bool operator==(const Point2d& p1, const Point2d& p2);
bool operator!=(const Point2d& p1, const Point2d& p2);

#endif