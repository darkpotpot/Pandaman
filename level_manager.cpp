#include "level_manager.h"
#include "asyncTaskManager.h"
#include "monster.h"
#include "simu_state.h"

int NB_LEVELS = 3;


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
    std::list<CellElem*> to_delete_elem;
    if(mSimulationTask!=NULL)
	{
		simuState = mSimulationTask->update(to_delete_elem);
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
    
    deleteCellElems(to_delete_elem);
    if (Food::noMoreFood())
    {
		nextLevel();
    }
    return AsyncTask::DS_cont;
}

void LevelManager::deleteCellElems(std::list<CellElem*>& to_delete_elem)
{

   CellElemType cell_elem_type;
   std::list<CellElem*>::iterator cell_it;
   for (cell_it=to_delete_elem.begin();cell_it!=to_delete_elem.end();cell_it++)
   {
        cell_elem_type = (*cell_it)->getType();
        if (cell_elem_type==MONSTER1)
        {
            mSimulationTask->removeEntity(dynamic_cast<Entity*>(*cell_it));
            mLevel->delete_monster(dynamic_cast<Monster*>(*cell_it));            
           }
        else if (cell_elem_type==FOOD)
        {
            mLevel->delete_food(dynamic_cast<Food*>(*cell_it));
        }

    }

}