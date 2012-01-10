#include "level_manager.h"
#include "asyncTaskManager.h"
#include "monster.h"
#include "simu_state.h"

int NB_LEVELS = 2;


LevelManager::LevelManager(WindowFramework *window, PandaFramework* framework):mDisplayer(LevelDisplayer(window, framework)), mControler(Controler(*framework)), mLevel(NULL), mSimulationTask(NULL), mCurrentLevel(0){
}

LevelManager::~LevelManager()
{
    cleanCurrentLevelIfn();
	remove();
}

void LevelManager::loadLevel(const char* pMapname){
    cleanCurrentLevelIfn();
    //
    mLevel = new Level(pMapname);
    mControler.setMainCharacter(mLevel->get_character());
    mSimulationTask = new SimulationTask(ClockObject::get_global_clock(), &mControler);
    mSimulationTask->addEntity(mLevel->get_character());
    for (std::list<Monster*>::iterator it = mLevel->get_monster_iterator(); it != mLevel->get_monster_list_end(); it++){
        mSimulationTask->addEntity(*it);
    }
    //PT(AsyncTaskManager) taskMgr = AsyncTaskManager::get_global_ptr();
    //taskMgr->add(mSimulationTask);
    //
    mDisplayer.displayLevel(*mLevel);
}

void LevelManager::cleanCurrentLevelIfn()
{
	if (mLevel==NULL)
	{return;}
     mDisplayer.undisplayLevel(*mLevel);
    if (mSimulationTask != NULL){
		delete mSimulationTask;
        //mSimulationTask->remove();
    }
    mControler.removeMainCharacter();
    delete mLevel;
	mLevel = NULL;
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

AsyncTask::DoneStatus LevelManager::do_task(){
	SimuState simuState;
    if(mSimulationTask!=NULL)
	{
		simuState = mSimulationTask->update();
	}
	if (simuState==LEVEL_FINISHED)
	{
		nextLevel();
	}
	else if (simuState==RESTART)
	{
		cleanCurrentLevelIfn();
		loadCurrentLevel();
	}
    return AsyncTask::DS_cont;
}