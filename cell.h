#ifndef Cell_H
#define Cell_H

#include "displayable.h"
#include <list>
using std::list;
enum CellElemType {EMPTY, WALL, CHARACTER, MONSTER1, FOOD, BONUS};

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
        Cell(int x, int y);
        int get_x() const{return m_x;}
        int get_y()const{return m_y;}
        ~Cell();
        bool is_accessible() const;
        void addElem(CellElem* elem);
        void removeElem(CellElem* elem);
        list<CellElem*> getCellElems() const;
    private:
        list<CellElem*> mElem;
        int m_x;
        int m_y;
};

#endif
