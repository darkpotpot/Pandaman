#ifndef LEVEL_MANAGER_H
#define LEVEL_MANAGER_H

#include <string>

#include "level_displayer.h"
#include "level.h"
#include "controler.h"
#include "simu.h"
#include "asyncTask.h"
#include "keyboard_manager.h"
#include "nodePath.h"

class LevelManager:public AsyncTask{
    public:
        LevelManager(WindowFramework *window, PandaFramework* framework, KeyboardManager* km);
		~LevelManager();
        void loadLevel(const char* pMapname);
        void nextLevel();
        void previousLevel();
        void start();
        void pause();
        ALLOC_DELETED_CHAIN(LevelManager);
    protected:
        virtual AsyncTask::DoneStatus do_task();
    private:
        void init_instruction_screen(WindowFramework *window);
        void deleteCellElems(std::list<CellElem*>& to_delete_elem);
        //
        Level* mLevel;
        LevelDisplayer mDisplayer;
        Controler mControler;
        SimulationTask* mSimulationTask;
        int mCurrentLevel;
        void loadCurrentLevel();
		void cleanCurrentLevelIfn();
        bool m_paused;
        NodePath* m_instruction_node;
};

#endif
