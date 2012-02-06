#include "follow_ia.h"


FollowIA::FollowIA(PathFinder* path_finder):PathFindingIA(path_finder)
{}


void FollowIA::set_last_known_pos(Point2d point)
{
    PathFindingIA::set_target(point);
    m_has_last_know_pos = true;
}

void FollowIA::compute_movement(Entity *entity, Grid* grid, int& x_res, int&y_res)
{
    PathFindingIA::compute_movement(entity, grid, x_res, y_res);
    if (path_empty())
    {
        m_has_last_know_pos = false;
        return;
    }
}

