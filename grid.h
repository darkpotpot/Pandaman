#ifndef Grid_H
#define Grid_H

#include <vector>
using std::vector;

#include "cell.h"
#include "displayable.h"
#include "event_manager.h"


class Grid:public Displayable
{
    public:
        Grid(int sizeX, int sizeY);
        ~Grid();
        bool is_accessible(int x, int y);
        list<CellElem*> getCellElems(int x, int y);
        void addElem(int x, int y, CellElem *elem);
        int getWidth();
        int getHeight();
        void move(int x_from, int y_from, int x_to, int y_to, CellElem *elem, EventManager& event_manager);
    private:
        vector<vector<Cell*> > mCells;
        int mWidth;
        int mHeight;
};

#endif
