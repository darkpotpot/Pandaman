#include "level_loader.h"
#include "cell.h"
#include "characterstate.h"


LevelLoader::LevelLoader(const char* pMapname){
    bool loadOkay = doc.LoadFile(pMapname);
    assert (loadOkay);
    TiXmlHandle levelHandle(&doc);
    TiXmlHandle mapHandle = levelHandle.FirstChild("map");
    initSize(mapHandle);
    TiXmlElement* child = mapHandle.FirstChild().ToElement();
    for(child; child; child=child->NextSiblingElement())
    {
        if (!strcmp(child->Value(), "tileset")){
            initTileset(child);
        }
        else if (!strcmp(child->Value(), "layer")){
            initLayer(child);
        }
        else{
            assert (false);
        }
    }
}

void LevelLoader::initSize(TiXmlHandle& mapHandle){
    TiXmlElement* mapElem = mapHandle.ToElement();
    mapElem->QueryIntAttribute("width", &mWidth);
    mapElem->QueryIntAttribute("height", &mHeight);
}


void LevelLoader::initTileset(TiXmlElement* tilesetElem){
    mTilesets[string(tilesetElem->Attribute("firstgid"))] = string(tilesetElem->Attribute("source"));
}

void LevelLoader::initLayer(TiXmlElement* layerElem){
    mLayers[string(layerElem->Attribute("name"))] = layerElem->FirstChildElement("data")->FirstChildElement("tile");
}

int LevelLoader::getWidth(){
    return mWidth;
}

int LevelLoader::getHeight(){
    return mHeight;
}

TiXmlElement* LevelLoader::getLayer(string layerName){
    return mLayers[layerName];
}

CellInfo LevelLoader::getCellElem(string gid){
    string tileset = mTilesets[gid];
	int cellType = -1, cellAdditionalInfo = -1;
    if (tileset == string("wall.tsx"))
	{
		cellType = WALL;
	}
    else if (tileset == string("panda.tsx"))
	{
        cellType = CHARACTER;
	}
    else if (tileset == string("monster1.tsx"))
	{
        cellType = MONSTER1;
	}
	else if (tileset == string("food.tsx"))
	{
        cellType = FOOD;
	}
	else if (tileset == string("speed.tsx"))
	{
		cellType = BONUS;
        cellAdditionalInfo = FAST;
	}
	else if (tileset == string("invincible.tsx"))
	{
		cellType = BONUS;
        cellAdditionalInfo = INVINCIBLE;
	}
	else if (tileset == string("drunk.tsx"))
	{
		cellType = BONUS;
        cellAdditionalInfo = DRUNK;
	}
	else if (tileset == string("random.tsx"))
	{
		cellType = BONUS;
        cellAdditionalInfo = RANDOM;
	}
    else
	{
        cellType = EMPTY;
	}
	CellInfo cell = {cellType, cellAdditionalInfo};
	return cell;
}
