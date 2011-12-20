#ifndef Grid_H
#define Grid_H

#include <vector>
using std::vector;

#include "cell.h"
#include "displayable.h"


class Grid:public Displayable
{
    public:
        bool is_accessible(int x, int y);
        bool loadMap(const char* pMapname);
        int mWidth;
        int mHeight;
        list<CellElem*> getCellElems(int x, int y);
        void addElem(int x, int y, CellElem *elem);
        void move(int x_from, int y_from, int x_to, int y_to, CellElem *elem);
    private:
        vector<vector<Cell*> > mCells;
};

#endif
