#include "pandaFramework.h"
#include "pandaSystem.h"
 
#include "genericAsyncTask.h"
#include "asyncTaskManager.h"

#include "simu.h"
#include "entity.h"
 
int main(int argc, char *argv[]) {
    PandaFramework framework;
    framework.open_framework(argc, argv);
    framework.set_window_title("My Panda3D Window");
    WindowFramework *window = framework.open_window();
    // Get the camera and store it in a variable.
    //camera = window->get_camera_group();
    
    //Grid grid = Grid();
    //generate grid display
    SimulationTask simu_task = SimulationTask();
    //chartacter = ...
    //character.set_displayer(displayer)
    //
    //simu_task.addEntity(character)
    Entity entity = Entity();
    simu_task.addEntity(entity);
    PT(AsyncTaskManager) taskMgr = AsyncTaskManager::get_global_ptr();     
    
    taskMgr->add(&simu_task);
    
    // Run the engine.
    framework.main_loop();
    // Shut down the engine when done.
    framework.close_framework();
    return (0);
}