#ifndef LEVEL_MANAGER_H
#define LEVEL_MANAGER_H

#include <string>

#include "level_displayer.h"
#include "level.h"
#include "controler.h"
#include "level_displayer.h"
#include "simu.h"


class LevelManager{
    public:
        LevelManager(WindowFramework *window, PandaFramework* framework);
        void loadLevel(const char* pMapname);
        void nextLevel();
        void previousLevel();
    private:
        Level* mLevel;
        LevelDisplayer mDisplayer;
        Controler mControler;
        PT(SimulationTask) mSimulationTask;
        int mCurrentLevel;
        void loadCurrentLevel();
};

#endif
