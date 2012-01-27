#include "explore_ia.h"
#include <utility>
#include <map>





PandaManPoint2d operator+(const PandaManPoint2d& p1, const PandaManPoint2d& p2)
{
    return PandaManPoint2d(p1.get_x()+ p2.get_x(), p1.get_y()+p2.get_y()); 
}

//necessary because in order to be used as key in map...need to be comparable...
bool operator<(const PandaManPoint2d& p1, const PandaManPoint2d& p2)
{
    if (p2.get_x()>p1.get_x())
        {return true;}
    else if ((p2.get_x()==p1.get_x())&&(p2.get_y()>p1.get_y()))
        {return true;}
    else
        {return false;}

}

list<PandaManPoint2d> init_directions()
{
        list<PandaManPoint2d> accessible_directions;
        accessible_directions.push_back(PandaManPoint2d(-1,0));
        accessible_directions.push_back(PandaManPoint2d(1,0));
        accessible_directions.push_back(PandaManPoint2d(0,-1));
        accessible_directions.push_back(PandaManPoint2d(0,1));
        return accessible_directions;
}

list<PandaManPoint2d>  ExploreIA::m_accessible_directions(init_directions());


ExploreIA::ExploreIA()
{}

ExploreIA::~ExploreIA()
{
//TODO : delete exploratyion map
}

void ExploreIA::compute_movement(Entity *entity, Grid* grid, int& x_res, int&y_res)
{
    list<PandaManPoint2d> accessible_pos;
    get_accessible_neightboors(grid, PandaManPoint2d(entity->get_x(), entity->get_y()), accessible_pos);
    int min_value =-1;
    int current_value = -1;
    PandaManPoint2d best_pos;
    for (list<PandaManPoint2d>::iterator it=accessible_pos.begin(); it!=accessible_pos.end(); it++)
        {
            std::map<PandaManPoint2d,int>::iterator res = m_exploration_map.find((*it));
            if (res!=m_exploration_map.end())
            {
                current_value = res->second;
            }
            else
            {
                m_exploration_map.insert(std::pair<PandaManPoint2d,int>((*it),0));
            current_value = 0;
            }
            if (min_value==-1||current_value<min_value)
            {
                min_value = current_value;
                best_pos = (*it);
            }
        }
    if (min_value==-1)
    {
        x_res = entity->get_x();
        y_res = entity->get_y();
        return;}
    else
    {
        m_exploration_map[best_pos] = m_exploration_map[best_pos]+1;
        x_res = best_pos.get_x();
        y_res = best_pos.get_y();
        return;
    }

}

list<PandaManPoint2d>& ExploreIA::get_accessible_direction()
{
    return m_accessible_directions;
}


void ExploreIA::get_accessible_neightboors(Grid* grid, PandaManPoint2d& current_pos, list<PandaManPoint2d>& res_list)
{
    PandaManPoint2d pos;
    list<PandaManPoint2d>& accessible_directions = get_accessible_direction();
    for (list<PandaManPoint2d>::iterator it = accessible_directions.begin();
        it!=accessible_directions.end();
        it++)
        {
            pos = current_pos+(*it);
            if (grid->is_accessible(pos.get_x(), pos.get_y()))
                { res_list.push_back(pos); }
        }
}