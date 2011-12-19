#ifndef IA_H
#define IA_H

#include "entity.h"

class IA{
   
public:
   IA();
   virtual void compute_movement(Entity *entity, Grid* grid, int& x_res, int&y_res);
    
};

class DirectionnalIA:public IA
{
public:
    DirectionnalIA();
    virtual void compute_movement(Entity *entity, Grid* grid, int& x_res, int&y_res);
    
private:
    int m_last_x_dir;
    int m_last_y_dir;
    bool is_at_crossroad(Entity* entity, Grid* grid);
};

#endif
