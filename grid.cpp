#include "grid.h"
#include "assert.h"
#include "tinyxml/tinyxml.h"
#include "cell.h"
#include <iostream>
using namespace std;


bool Grid::is_accessible(int x, int y)
{return mCells[x][y]->is_accessible();}

bool Grid::loadMap(const char* pMapname){
    TiXmlDocument doc(pMapname);
    bool loadOkay = doc.LoadFile();
    assert (loadOkay);
    TiXmlHandle docHandle(&doc);
    TiXmlElement* elem = docHandle.FirstChild("map").ToElement();
    elem->QueryIntAttribute("width", &mWidth);
    elem->QueryIntAttribute("height", &mHeight);
    //
    mCells.clear();
    mCells.resize(mHeight);
    for (int i = 0; i < mHeight; ++i){
        mCells[i].resize(mWidth);
    }
    TiXmlElement* tileElem =docHandle.FirstChild("map").FirstChild("layer").FirstChild("data").FirstChild("tile").ToElement() ;
    assert (elem);
    for (int i=mHeight - 1; i > -1; i--){ //panda is not sorted in the same order than the map
        for (int j=0; j < mWidth; j++){
            mCells[j][i] = new Cell();
            switch (atoi(tileElem->Attribute("gid"))){
                case 1:
                    mCells[j][i]->addElem(new Wall());
                    break;
            }
            tileElem = tileElem->NextSiblingElement();
        }
    }
    return true;
}

list<CellElem*> Grid::getCellElems(int x, int y){
    return mCells[x][y]->getCellElems();
}

void Grid::addElem(int x, int y, CellElem *elem)
{
    mCells[x][y]->addElem(elem);
}

void Grid::move(int x_from, int y_from, int x_to, int y_to, CellElem *elem)
{
    mCells[x_from][y_from]->removeElem(elem);
    mCells[x_to][y_to]->addElem(elem);
}
