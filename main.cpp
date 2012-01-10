#include "pandaFramework.h"
#include "pandaSystem.h"

#include "genericAsyncTask.h"
#include "asyncTaskManager.h"
#include "cIntervalManager.h"
#include <stdlib.h>
#include <time.h>



#include "level_manager.h"


AsyncTask::DoneStatus update_lerp(GenericAsyncTask* task, void* data) {
    ((CIntervalManager*)data)->step();
    return AsyncTask::DS_cont;
    }

void nextLevel(const Event * theEvent, void * data){
    LevelManager* levelManager = (LevelManager*)data;
    levelManager->nextLevel();
}

void previousLevel(const Event * theEvent, void * data){
    LevelManager* levelManager = (LevelManager*)data;
    levelManager->previousLevel();
}

int main(int argc, char *argv[]) {
    srand(time(NULL));
    PandaFramework framework;
    framework.open_framework(argc, argv);
    framework.set_window_title("My Panda3D Window");
    WindowFramework *window = framework.open_window();
    window->enable_keyboard();


    LevelManager level_manager = LevelManager(window, &framework);
    level_manager.nextLevel();
    framework.define_key("+", "LevelUp", nextLevel, (void *)&level_manager); 
    framework.define_key("-", "LevelDown", previousLevel, (void *)&level_manager); 

    PT(AsyncTaskManager) taskMgr = AsyncTaskManager::get_global_ptr();
    taskMgr->add(new GenericAsyncTask("Update lerp", &update_lerp, (void*) CIntervalManager::get_global_ptr()));
	taskMgr->add(&level_manager);
    // Run the engine.
    framework.main_loop();
    // Shut down the engine when done.
    framework.close_framework();
    return (0);
}
