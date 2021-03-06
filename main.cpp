#include "pandaFramework.h"
#include "pandaSystem.h"


#include "genericAsyncTask.h"
#include "asyncTaskManager.h"
#include "cIntervalManager.h"

#include <stdlib.h>
#include <time.h>

#include "detection.h"
#include "level_manager.h"

#include "keyboard_manager.h"


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


void pause(const Event * theEvent, void * data){
    LevelManager* levelManager = (LevelManager*)data;
    levelManager->pause();

}


void start(const Event * theEvent, void * data){
    LevelManager* levelManager = (LevelManager*)data;
    levelManager->start();

}
int main(int argc, char *argv[]) {
    srand(time(NULL));
    PandaFramework framework;
    framework.open_framework(argc, argv);
    framework.set_window_title("My Panda3D Window");
    WindowFramework *window = framework.open_window();
    window->enable_keyboard();

	KeyboardManager km(&framework);
    LevelManager level_manager = LevelManager(window, &framework, &km);
    level_manager.nextLevel();
	//hack pour changer de niveau manuellement
    framework.define_key("+", "LevelUp", nextLevel, &level_manager); 
    framework.define_key("-", "LevelDown", previousLevel, &level_manager);
    framework.define_key("space", "start", start, &level_manager);
    framework.define_key("escape", "pause", pause, &level_manager);

    PT(AsyncTaskManager) taskMgr = AsyncTaskManager::get_global_ptr();
    taskMgr->add(new GenericAsyncTask("Update lerp", &update_lerp, (void*) CIntervalManager::get_global_ptr()));
	taskMgr->add(&level_manager);

    // Run the engine.
    framework.main_loop();
    // Shut down the engine when done.
    framework.close_framework();
    return (0);
}
