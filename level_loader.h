#ifndef LEVEL_LOADER_H
#define LEVEL_LOADER_H

#include "tinyxml/tinyxml.h"
#include <map>
#include <string>

using namespace std;

struct CellInfo{
	int type;
	int additionalInfo;
};


class LevelLoader{
    public:
        LevelLoader(const char* pMapname);
        int getWidth();
        int getHeight();
        TiXmlElement* getLayer(string layerName);
        CellInfo getCellElem(string gid);
    private:
        int mWidth;
        int mHeight;
        map<string, string> mTilesets;
        map<string, TiXmlElement*> mLayers;
        void initSize(TiXmlHandle& mapHandle);
        void initTileset(TiXmlElement* tilesetElem);
        void initLayer(TiXmlElement* layerElem);
        TiXmlDocument doc; //needed cause if we don't keep it in memory, everything is freed
};


#endif
