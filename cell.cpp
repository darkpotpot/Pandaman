#include "cell.h"


bool CellElem::blocks(){
    return false;
}

bool Wall::blocks(){
    return true;
}

Cell::Cell() {}


void Cell::addElem(CellElem* elem){
    mElem.push_back(elem);
}

bool Cell::is_accessible(){
    vector<CellElem*>::iterator it;
    for ( it=mElem.begin() ; it < mElem.end(); it++ ){
        if ((*it)->blocks() == true) {
            return false;
        }
    }
    return true;
}

vector<CellElem*> Cell::getCellElems(){
    return mElem;
}


