#ifndef GridDisplay_H
#define GridDisplay_H

#include "grid.h"
#include "pandaFramework.h"
#include "geoMipTerrain.h"

class GridDisplayer{
    public:
        GridDisplayer(NodePath* parentNode);
        void display_grid(Grid* grid);

    private:
        GeoMipTerrain* mTerrain;
        NodePath* mParentNode;
};


#endif
