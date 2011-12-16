#include "pandaFramework.h"
#include "pandaSystem.h"

#include "genericAsyncTask.h"
#include "asyncTaskManager.h"
#include "cIntervalManager.h"

#include "level_manager.h"
//#include "level_displayer.h"


AsyncTask::DoneStatus update_lerp(GenericAsyncTask* task, void* data) {
    ((CIntervalManager*)data)->step();
    return AsyncTask::DS_cont;
    }


int main(int argc, char *argv[]) {
    PandaFramework framework;
    framework.open_framework(argc, argv);
    framework.set_window_title("My Panda3D Window");
    WindowFramework *window = framework.open_window();
    window->enable_keyboard();

    LevelManager level_manager = LevelManager(window, &framework);//new LevelDisplayer(window, &framework), new Controler(framework));
    level_manager.loadLevel("resources/map/level01.tmx");

    PT(AsyncTaskManager) taskMgr = AsyncTaskManager::get_global_ptr();
    taskMgr->add(new GenericAsyncTask("Update lerp", &update_lerp, (void*) CIntervalManager::get_global_ptr()));
    // Run the engine.
    framework.main_loop();
    // Shut down the engine when done.
    framework.close_framework();
    return (0);
}
