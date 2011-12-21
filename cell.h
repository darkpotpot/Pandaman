#ifndef Cell_H
#define Cell_H

#include "displayable.h"
#include <list>
using std::list;
enum CellElemType {EMPTY, WALL, CHARACTER, MONSTER1};

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
        ~Cell();
        bool is_accessible();
        void addElem(CellElem* elem);
        void removeElem(CellElem* elem);
        list<CellElem*> getCellElems();
    private:
        list<CellElem*> mElem;
};

#endif
