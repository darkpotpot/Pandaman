#include "level_manager.h"
#include "asyncTaskManager.h"
#include "monster.h"
#include "simu_state.h"
//

#include "cardMaker.h"
#include "texture.h"
#include "texturePool.h"
//
int NB_LEVELS = 4;


LevelManager::LevelManager(WindowFramework *window, PandaFramework* framework, KeyboardManager* km):mDisplayer(LevelDisplayer(window, framework, km)), mControler(Controler(km)), mLevel(NULL), mSimulationTask(NULL), mCurrentLevel(0), m_paused(true)
{
    init_instruction_screen(window);
}

LevelManager::~LevelManager()
{
    cleanCurrentLevelIfn();
	remove();
}

void LevelManager::init_instruction_screen(WindowFramework *window)
{
PT(Texture) tex;
tex = TexturePool::load_texture( "resources/instructions.png"); 
CardMaker cm("cardMaker");
cm.set_frame_fullscreen_quad();
PT(PandaNode) readyCard = cm.generate(); 
m_instruction_node = new NodePath(readyCard);
m_instruction_node->set_texture( tex ); 
m_instruction_node->reparent_to(window->get_render_2d());
}

void LevelManager::start()
{
    cout<<"starting!!"<<endl;
    m_instruction_node->hide();
    m_paused = false;

}
void LevelManager::pause()
{
   m_instruction_node->show();
   m_paused = true;

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
    if (m_paused)
    {    return AsyncTask::DS_cont;}
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
    else {
        deleteCellElems(to_delete_elem);
        if (Food::noMoreFood())
        {
		    nextLevel();
        }
    }
    return AsyncTask::DS_cont;
}

void LevelManager::deleteCellElems(std::list<CellElem*>& to_delete_elem)
{
    //by using front and remove we make sure that each element is only 
    //deleted once(remove removes all values equal to passed value)
    CellElemType cell_elem_type;
    CellElem* cell_elem;
    while (!to_delete_elem.empty())
    {
        cell_elem = to_delete_elem.front();
        to_delete_elem.remove(cell_elem);
        cell_elem_type = cell_elem->getType();
        if (cell_elem_type==MONSTER1)
        {
            mSimulationTask->removeEntity(dynamic_cast<Entity*>(cell_elem));
            mLevel->delete_monster(dynamic_cast<Monster*>(cell_elem));            
           }
        else if (cell_elem_type==FOOD)
        {
            mLevel->delete_food(dynamic_cast<Food*>(cell_elem));
        }
        else if (cell_elem_type==BONUS)
        {
            mLevel->delete_bonus(dynamic_cast<Bonus*>(cell_elem));
        }
    
    }

}