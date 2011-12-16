#ifndef LEVEL_MANAGER_H
#define LEVEL_MANAGER_H

#include <string>

#include "level_displayer.h"
#include "level.h"
#include "controler.h"
#include "level_displayer.h"


class LevelManager{
    public:
        //LevelManager(LevelDisplayer displayer, Controler* controler);
        LevelManager(WindowFramework *window, PandaFramework* framework);
        bool loadLevel(const char* pMapname);
    private:
        Level mLevel;
        LevelDisplayer mDisplayer;
        Controler mControler;
};

#endif
