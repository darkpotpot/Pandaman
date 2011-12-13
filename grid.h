#ifndef Grid_H
#define Grid_H

#include "cell.h"
#include <vector>
using std::vector;

class Grid
{
    public:
        Grid();
        bool is_accessible(int x, int y);
        bool loadMap(const char* pMapname);
        int mWidth;
        int mHeight;
    private:
        vector<vector<Cell*> > mCells;
};

#endif
