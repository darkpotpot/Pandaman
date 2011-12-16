#ifndef HEIGHTFIELD_DISPLAY_H
#define HEIGHTFIELD_DISPLAY_H

#include "grid.h"
#include "pandaFramework.h"
#include "geoMipTerrain.h"
#include "displayer.h"

class HeightfieldDisplayer:public Displayer{
    public:
        HeightfieldDisplayer(Grid* grid, NodePath* parentNode);
    private:
        GeoMipTerrain mTerrain;
        NodePath* mParentNode;
};


#endif
