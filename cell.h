#ifndef Cell_H
#define Cell_H

#include <vector>
using std::vector;

class CellElem{
    public:
        virtual bool blocks();
};

class Wall:public CellElem{
    public:
        Wall();
        bool blocks();
};


class Cell{
    public:
        Cell();
        bool is_accessible();
        void addElem(CellElem* elem);
    private:
        vector<CellElem*> mElem;
};

#endif
