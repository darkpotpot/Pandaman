#include "point2d.h"

Point2d operator+(const Point2d& p1, const Point2d& p2)
{
    return Point2d(p1.get_x()+ p2.get_x(), p1.get_y()+p2.get_y()); 
}

//necessary because in order to be used as key in map...need to be comparable...
bool operator<(const Point2d& p1, const Point2d& p2)
{
    if (p2.get_x()>p1.get_x())
        {return true;}
    else if ((p2.get_x()==p1.get_x())&&(p2.get_y()>p1.get_y()))
        {return true;}
    else
        {return false;}

}

bool operator==(const Point2d& p1, const Point2d& p2)
{return ((p1.get_x()==p2.get_x())&&
         (p1.get_y()==p2.get_y()));
}

bool operator!=(const Point2d& p1, const Point2d& p2){return !(p1==p2);}
