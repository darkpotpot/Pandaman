#include "cell.h"

bool CellElem::blocks(){
    return false;
}

bool Wall::blocks(){
    return true;
}

Cell::Cell(int x, int y):m_x(x), m_y(y) {}

Cell::~Cell(){
    list<CellElem*>::iterator it;
    for ( it=mElem.begin() ; it != mElem.end(); it++ ){
        delete (*it);
    }
    mElem.clear();
}

void Cell::addElem(CellElem* elem){
    mElem.push_back(elem);
}

void Cell::removeElem(CellElem* elem)
{
    mElem.remove(elem);
}

bool Cell::is_accessible() const{
    list<CellElem*>::const_iterator it;
    for ( it=mElem.begin() ; it != mElem.end(); it++ ){
        if ((*it)->blocks() == true) {
            return false;
        }
    }
    return true;
}

list<CellElem*> Cell::getCellElems() const{
    return mElem;
}


