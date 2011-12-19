#include "ia.h"
#include <stdlib.h>


IA::IA()
{}

void IA::compute_movement(Entity *entity, Grid* grid, int& x_res, int&y_res)
{
    int x =entity->get_x();
    int y =entity->get_y();
    int val;
    int dir;
    
    if (rand()%100>50)
        { dir = 1; }
    else
        {dir = -1;}
    if (rand()%100>50)
        {x = x+dir;}
    else
        {y=y+dir;}
    while (!grid->is_accessible(x,y))
        {
        x = entity->get_x();
        y = entity->get_y();
        if (rand()%100>50)
            { dir = 1; }
        else
            {dir = -1;}
        if (rand()%100>50)
            {x = x+dir;}
        else
            {y=y+dir;}
        }
    x_res = x;
    y_res = y;
}

DirectionnalIA::DirectionnalIA():m_last_x_dir(0), m_last_y_dir(0)
{}

void DirectionnalIA::compute_movement(Entity *entity, Grid* grid, int& x_res, int&y_res)
{
    int x =entity->get_x();
    int y =entity->get_y();
    if ((m_last_x_dir!=0 || m_last_y_dir!=0))
    {
        if (grid->is_accessible(x+m_last_x_dir,y+m_last_y_dir))
        {
            if(!is_at_crossroad(entity, grid)||rand()%100>70)
            {
                x_res = x+m_last_x_dir;
                y_res = y+m_last_y_dir;
                return;
            }
        }
    }

    int val;
    int dir;
    if (rand()%100>50)
        { dir = 1; }
    else
        {dir = -1;}
    if (rand()%100>50)
        {x = x+dir;
        m_last_x_dir=dir;
        m_last_y_dir=0;
        }
    else
        {y=y+dir;
        m_last_x_dir = 0;
        m_last_y_dir = dir;
        }
    while (!grid->is_accessible(x,y))
    {
        x = entity->get_x();
        y = entity->get_y();
        if (rand()%100>50)
            { dir = 1; }
        else
            {dir = -1;}
        if (rand()%100>50)
        {
            x = x+dir;
            m_last_x_dir=dir;
            m_last_y_dir=0;
        }
        else
        {
            y=y+dir;
            m_last_x_dir = 0;
            m_last_y_dir = dir;
        }
    }
    x_res = x;
    y_res = y;
}

bool DirectionnalIA::is_at_crossroad(Entity* entity, Grid* grid)
{
    int nb_free_cases=0;
    int x = entity->get_x();
    int y= entity->get_y();
    if (grid->is_accessible(x-1, y))
        { nb_free_cases = nb_free_cases+1; }
    if (grid->is_accessible(x+1, y))
        { nb_free_cases = nb_free_cases+1; }
    if (grid->is_accessible(x, y-1))
        { nb_free_cases = nb_free_cases+1; }
    if (grid->is_accessible(x, y+1))
        { nb_free_cases = nb_free_cases+1; }
    return nb_free_cases>2;
}
