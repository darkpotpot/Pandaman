#include "level_manager.h"
#include "asyncTaskManager.h"


//LevelManager::LevelManager(LevelDisplayer* displayer, Controler* controler):mDisplayer(displayer), mControler(controler)
//{}
LevelManager::LevelManager(WindowFramework *window, PandaFramework* framework):mDisplayer(LevelDisplayer(window, framework)), mControler(Controler(*framework)){
}


bool LevelManager::loadLevel(const char* pMapname){
    mLevel.grid = Grid();
    mLevel.grid.loadMap(pMapname);
    mLevel.panda = MainCharacter(1, 1, &mLevel.grid);
    //
    mControler.setMainCharacter(&mLevel.panda);
    mLevel.simu = SimulationTask(ClockObject::get_global_clock(), &mControler);
    mLevel.simu.addEntity(&mLevel.panda);
    PT(AsyncTaskManager) taskMgr = AsyncTaskManager::get_global_ptr();
    taskMgr->add(&mLevel.simu);
    //
    mDisplayer.displayLevel(mLevel);
}
