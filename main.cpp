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
#include "character_displayer.h"
 
int main(int argc, char *argv[]) {
    PandaFramework framework;
    framework.open_framework(argc, argv);
    framework.set_window_title("My Panda3D Window");
    WindowFramework *window = framework.open_window();
    window->enable_keyboard(); 
    // Get the camera and store it in a variable.

    Grid grid = Grid();
    grid.loadMap("resources/map/level01.tmx");
    text_display(grid);
    //generate grid display
    SimulationTask simu_task = SimulationTask();
    //chartacter = ...
    //character.set_displayer(displayer)
    //
    //simu_task.addEntity(character)
    //Entity entity = Entity(&grid);  
    //simu_task.addEntity(entity);
    MainCharacter c = MainCharacter(1,1,&grid);
    simu_task.addEntity(&c);
    CharacterDisplayer char_displayer = CharacterDisplayer("panda-model", window, &framework);
    c.set_displayer(&char_displayer);
    //window->setup_trackball();
    Controler controler = Controler(framework, &c);
    PT(AsyncTaskManager) taskMgr = AsyncTaskManager::get_global_ptr();     

    taskMgr->add(&simu_task);
    NodePath camera = window->get_camera_group();
    camera.set_pos(0.,0.,500.);
    camera.set_hpr(0,-90.,0);
    // Run the engine.
    framework.main_loop();
    // Shut down the engine when done.
    framework.close_framework();
    return (0);
}
