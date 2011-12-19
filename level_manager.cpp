#include "level_manager.h"
#include "asyncTaskManager.h"
#include "monster.h"
//LevelManager::LevelManager(LevelDisplayer* displayer, Controler* controler):mDisplayer(displayer), mControler(controler)
//{}
LevelManager::LevelManager(WindowFramework *window, PandaFramework* framework):mDisplayer(LevelDisplayer(window, framework)), mControler(Controler(*framework)){
}


bool LevelManager::loadLevel(const char* pMapname){
    mLevel.set_grid(new Grid());
    mLevel.get_grid()->loadMap(pMapname);
    mLevel.set_character(new MainCharacter(1, 1, mLevel.get_grid()));
    mControler.setMainCharacter(mLevel.get_character());
    mLevel.set_simulation(new SimulationTask(ClockObject::get_global_clock(), &mControler));
    mLevel.get_simulation()->addEntity(mLevel.get_character());
    //
    Monster *monster = new Monster(1,2,mLevel.get_grid());
    mLevel.add_monster(monster);
    mLevel.get_simulation()->addEntity(&(*monster));
    //
    monster = new Monster(2,2,mLevel.get_grid());
    mLevel.add_monster(monster);
    mLevel.get_simulation()->addEntity(&(*monster));
    PT(AsyncTaskManager) taskMgr = AsyncTaskManager::get_global_ptr();
    taskMgr->add(mLevel.get_simulation());
    //

    mDisplayer.displayLevel(mLevel);
}
