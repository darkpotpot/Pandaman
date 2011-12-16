#include "pandaFramework.h"
#include "pandaSystem.h"

#include "genericAsyncTask.h"
#include "asyncTaskManager.h"
#include "cIntervalManager.h"

#include "simu.h"
#include "entity.h"
#include "grid.h"
#include "grid_display.h"
#include "controler.h"
#include "character.h"
#include "character_displayer.h"
#include "cell_displayer.h"
#include "world_camera.h"
#include "monster.h"


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

    Grid grid = Grid();
    grid.loadMap("resources/map/level01.tmx");
    GridDisplayer gDisplayer = GridDisplayer(window);
    gDisplayer.display_grid(grid);
    initCellElemDisplayers(grid, window, &framework);
    WorldCamera camera = WorldCamera(window);
    camera.seeAll(grid);

    MainCharacter c = MainCharacter(1,1,&grid);
    CharacterDisplayer char_displayer = CharacterDisplayer("panda-model", window, &framework);
    c.set_displayer(&char_displayer);
    Controler controler = Controler(framework, &c);
    SimulationTask simu_task = SimulationTask(ClockObject::get_global_clock(), &controler);
    simu_task.addEntity(&c);
    
    Monster m = Monster(5,5,&grid);
    simu_task.addEntity(m);

    PT(AsyncTaskManager) taskMgr = AsyncTaskManager::get_global_ptr();

    taskMgr->add(&simu_task);
    //--
    taskMgr->add(new GenericAsyncTask("Update lerp", &update_lerp, (void*) CIntervalManager::get_global_ptr()));

    // Run the engine.
    framework.main_loop();
    // Shut down the engine when done.
    framework.close_framework();
    return (0);
}
