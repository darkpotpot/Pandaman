#include "grid.h"
#include "assert.h"
#include "cell.h"
#include "event.h"

class CollisionEvent;

#include <iostream>
using namespace std;

Grid::Grid(int width, int height):mWidth(width), mHeight(height){
    mCells.clear();
    mCells.resize(mHeight);
    for (int i = 0; i < mHeight; ++i){
        mCells[i].resize(mWidth);
    }
    for (int i=0; i < width; i++){
        for (int j=0; j<height; j++){
            mCells[i][j] = new Cell();
        }
    }
}

//Grid::~Grid(){
    //for (int i=0; i<mWidth; i++){
        //for (int j=0; j<mHeight; j++){
            //vector<CellElem*> elems = getCellElems(i, j);
            //vector<CellElem*>::iterator it;
            //for ( it=elems.begin() ; it < elems.end(); it++ ){
                //delete (*it);
            //}
            //delete mCells[i][j];
        //}
    //}

//}

bool Grid::is_accessible(int x, int y)
{return mCells[x][y]->is_accessible();}


list<CellElem*> Grid::getCellElems(int x, int y){
    return mCells[x][y]->getCellElems();
}

void Grid::addElem(int x, int y, CellElem *elem)
{
    mCells[x][y]->addElem(elem);
}

int Grid::getWidth(){
    return mWidth;
}

int Grid::getHeight(){
    return mHeight;
}

void Grid::move(int x_from, int y_from, int x_to, int y_to, CellElem* elem, EventManager& event_manager)
{
    mCells[x_from][y_from]->removeElem(elem);
    list<CellElem*> cell_elem_list =  getCellElems(x_to, y_to);
    if (!cell_elem_list.empty())
    {
        list<CellElem*>::iterator it;
        for (it=cell_elem_list.begin();it!=cell_elem_list.end();it++)
        {
        event_manager.addEvent(new CollisionEvent(elem, (*it), this));
        }
            
    }
        
    mCells[x_to][y_to]->addElem(elem);
}
