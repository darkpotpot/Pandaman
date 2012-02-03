#include "follow_ia.h"

FollowIA::FollowIA(PathFinder* path_finder):m_path_finder(path_finder), m_last_known_pos(-1,-1), m_has_last_know_pos(false)
{}

FollowIA::~FollowIA()
{
    if (m_path_finder!=NULL)
    { 
    delete m_path_finder;
    m_path_finder = NULL;
    }
}
void FollowIA::set_last_known_pos(Point2d point)
{
    m_has_last_know_pos = true;
    if(point!=m_last_known_pos)
    {
        m_last_known_pos = point;
    }
    m_path.clear();
}

void FollowIA::compute_movement(Entity *entity, Grid* grid, int& x_res, int&y_res)
{
    x_res = entity->get_x();
    y_res = entity->get_y();
    if(!m_has_last_know_pos) 
        { return; }
    if (m_path.empty()||!is_path_up_to_date(entity))
    {
        m_path = m_path_finder->find_best_path(grid->getCell(entity->get_x(), entity->get_y()), 
                                              grid->getCell(m_last_known_pos.get_x(), m_last_known_pos.get_y()));
    }
    if (!m_path.empty())
    {
        m_path.pop_front();
    }
    if (m_path.empty())
    {
        m_has_last_know_pos = false;
        return;
    }
    const Cell* next = m_path.front();
    x_res = next->get_x();
    y_res = next->get_y();
}

bool FollowIA::is_path_up_to_date(Entity *entity)
{
    int x_start = entity->get_x();
    int y_start = entity->get_y();
    const Cell* first = m_path.front();
    if ((first->get_x()!=x_start)||(first->get_y()!=y_start))
        {return false;}
    const Cell* end = m_path.back();
    if ((end->get_x()!=m_last_known_pos.get_x())||(end->get_y()!=m_last_known_pos.get_y()))
        {return false;}
    return true;

}
