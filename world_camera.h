#ifndef WordlCamera_H
#define WordlCamera_H

#include "grid.h"
#include "pandaFramework.h"

class WorldCamera{
    public:
        WorldCamera(WindowFramework* window);
        void seeAll(Grid& grid);
    private:
        NodePath mCamera;
};


#endif
