#include "grid.h"
#include "assert.h"
#include "tinyxml/tinyxml.h"
#include "cell.h"


Grid::Grid() {}

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
    TiXmlHandle tileHandle = docHandle.FirstChild("map").FirstChild("layer").FirstChild("data");
    TiXmlElement* tileElem;
    assert (elem);
    for (int i=0; i < mHeight; i++){
        for (int j=0; j < mWidth; j++){
            tileElem = tileHandle.ChildElement("tile", i*mHeight + j).ToElement();
            mCells[i][j] = new Cell();
            switch (atoi(tileElem->Attribute("gid"))){
                case 1:
                    mCells[i][j]->addElem(new Wall());
                    break;
            }
        }
    }
    // add call to the displayer
}

