#ifndef Cell_H
#define Cell_H

#include "displayable.h"
#include <vector>
using std::vector;
enum CellElemType {EMPTY, WALL};

class CellElem:public Displayable{
    public:
        virtual const CellElemType getType(){return EMPTY;};
        virtual bool blocks();
};

class Wall:public CellElem{
    public:
        const CellElemType getType(){return WALL;};
        bool blocks();
};


class Cell{
    public:
        Cell();
        bool is_accessible();
        void addElem(CellElem* elem);
        vector<CellElem*> getCellElems();
    private:
        vector<CellElem*> mElem;
};

#endif
