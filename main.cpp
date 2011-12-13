#include "pandaFramework.h"
#include "pandaSystem.h"
 
#include "genericAsyncTask.h"
#include "asyncTaskManager.h"

#include "simu.h"
#include "entity.h"
#include "grid.h"
#include "grid_display.h"
#include "controler.h"
#include "character.h"
 
int main(int argc, char *argv[]) {
    PandaFramework framework;
    framework.open_framework(argc, argv);
    framework.set_window_title("My Panda3D Window");
    WindowFramework *window = framework.open_window();
    window->enable_keyboard(); 
    // Get the camera and store it in a variable.
    //camera = window->get_camera_group();
    //dump_to_stdout("test.xml");
    Grid grid = Grid();
    grid.loadMap("resources/map/level01.tmx");
    GridDisplayer gDisplayer = GridDisplayer(window);
    gDisplayer.display_grid(grid);

    window->setup_trackball();

    //text_display(grid);
    //generate grid display
    SimulationTask simu_task = SimulationTask();
    //chartacter = ...
    //character.set_displayer(displayer)
    //
    //simu_task.addEntity(character)
    //Entity entity = Entity(&grid);  
    Character c = Character(&grid);
    //simu_task.addEntity(entity);
    c.update();
    ((Entity*)(&c))->update();
    simu_task.addEntity(&c);
    
    Controler controler = Controler(framework, &c);
    PT(AsyncTaskManager) taskMgr = AsyncTaskManager::get_global_ptr();     
    
    taskMgr->add(&simu_task);
    
    // Run the engine.
    framework.main_loop();
    // Shut down the engine when done.
    framework.close_framework();
    return (0);
}
