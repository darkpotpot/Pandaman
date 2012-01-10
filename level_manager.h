#ifndef LEVEL_MANAGER_H
#define LEVEL_MANAGER_H

#include <string>

#include "level_displayer.h"
#include "level.h"
#include "controler.h"
#include "level_displayer.h"
#include "simu.h"
#include "asyncTask.h"


class LevelManager:public AsyncTask{
    public:
        LevelManager(WindowFramework *window, PandaFramework* framework);
		~LevelManager();
        void loadLevel(const char* pMapname);
        void nextLevel();
        void previousLevel();
        ALLOC_DELETED_CHAIN(LevelManager);
    protected:
        virtual AsyncTask::DoneStatus do_task();
    private:
        Level* mLevel;
        LevelDisplayer mDisplayer;
        Controler mControler;
        SimulationTask* mSimulationTask;
        int mCurrentLevel;
        void loadCurrentLevel();
		void cleanCurrentLevelIfn();
};

#endif
