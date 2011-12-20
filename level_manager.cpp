#include "level_manager.h"
#include "asyncTaskManager.h"
#include "monster.h"

int NB_LEVELS = 2;


LevelManager::LevelManager(WindowFramework *window, PandaFramework* framework):mDisplayer(LevelDisplayer(window, framework)), mControler(Controler(*framework)), mLevel(NULL), mSimulationTask(NULL), mCurrentLevel(0){
}


void LevelManager::loadLevel(const char* pMapname){
    if (mLevel != NULL){
        mDisplayer.undisplayLevel(*mLevel);
    }
    PT(AsyncTaskManager) taskMgr = AsyncTaskManager::get_global_ptr();
    if (mSimulationTask != NULL){
        mSimulationTask->remove();
    }
    mControler.removeMainCharacter();
    delete mLevel;
    //
    mLevel = new Level(pMapname);
    mControler.setMainCharacter(mLevel->get_character());
    mSimulationTask = new SimulationTask(ClockObject::get_global_clock(), &mControler);
    mSimulationTask->addEntity(mLevel->get_character());

    Monster *monster = new Monster(1,2,mLevel->get_grid());
    mLevel->addEntity(monster);
    mSimulationTask->addEntity(&(*monster));
    //
    monster = new Monster(2,2,mLevel->get_grid());
    mLevel->addEntity(monster);
    mSimulationTask->addEntity(&(*monster));

    taskMgr->add(mSimulationTask);
    //
    mDisplayer.displayLevel(*mLevel);
}

void LevelManager::loadCurrentLevel(){
    stringstream sstm;
    sstm << "resources/map/level" << mCurrentLevel << ".tmx";
    loadLevel(sstm.str().c_str());
}

void LevelManager::nextLevel(){
    if (mCurrentLevel == NB_LEVELS){
        return;
    }
    mCurrentLevel += 1;
    loadCurrentLevel();
}

void LevelManager::previousLevel(){
    if (mCurrentLevel <= 1){
        return;
    }
    mCurrentLevel -= 1;
    loadCurrentLevel();
}
