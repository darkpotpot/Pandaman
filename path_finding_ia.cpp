#include "path_finding_ia.h"

PathFindingIA::PathFindingIA(PathFinder* path_finder):m_path_finder(path_finder), m_target_pos(-1,-1), m_has_target(false)
{}

PathFindingIA::~PathFindingIA()
{
    if (m_path_finder!=NULL)
    { 
    delete m_path_finder;
    m_path_finder = NULL;
    }
}
void PathFindingIA::set_target(Point2d point)
{
    m_has_target = true;
    if(point!=m_target_pos)
    {
        m_target_pos = point;
    }
    m_path.clear();
}

void PathFindingIA::compute_movement(Entity *entity, Grid* grid, int& x_res, int&y_res)
{
    x_res = entity->get_x();
    y_res = entity->get_y();
    if(!m_has_target) 
        { return; }
    if (m_path.empty()||!is_path_up_to_date(entity))
    {
        m_path = m_path_finder->find_best_path(grid->getCell(entity->get_x(), entity->get_y()), 
                                              grid->getCell(m_target_pos.get_x(), m_target_pos.get_y()));
    }
    if (!m_path.empty())
    {
        m_path.pop_front();
    }
    if (m_path.empty())
    {
        return;
    }
    const Cell* next = m_path.front();
    x_res = next->get_x();
    y_res = next->get_y();
}

bool PathFindingIA::is_path_up_to_date(Entity *entity)
{
    int x_start = entity->get_x();
    int y_start = entity->get_y();
    const Cell* first = m_path.front();
    if ((first->get_x()!=x_start)||(first->get_y()!=y_start))
        {return false;}
    const Cell* end = m_path.back();
    if ((end->get_x()!=m_target_pos.get_x())||(end->get_y()!=m_target_pos.get_y()))
        {return false;}
    return true;

}