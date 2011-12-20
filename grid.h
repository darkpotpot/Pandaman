#ifndef Grid_H
#define Grid_H

#include <vector>
using std::vector;

#include "cell.h"
#include "displayable.h"


class Grid:public Displayable
{
    public:
        Grid(int sizeX, int sizeY);
        bool is_accessible(int x, int y);
        list<CellElem*> getCellElems(int x, int y);
        void addElem(int x, int y, CellElem *elem);
        int getWidth();
        int getHeight();
    private:
        vector<vector<Cell*> > mCells;
        int mWidth;
        int mHeight;
};

#endif
