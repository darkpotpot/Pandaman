#include "level_displayer.h"
#include "heightfield_displayer.h"
#include "cell_displayer.h"

LevelDisplayer::LevelDisplayer(WindowFramework* window, PandaFramework* framework):mWindow(window), mFramework(framework),mModelManager(ModelManager(window, framework)), mCamera(WorldCamera(window, framework)){
}


void LevelDisplayer::displayLevel(Level& level){
    level.get_grid()->set_displayer(new HeightfieldDisplayer(level.get_grid(), level.get_root_node()));
    //
    initCellElemDisplayers(*level.get_grid(), level.get_root_node(), &mModelManager);
	mCamera.displayLevel(&level);
    level.get_root_node()->reparent_to(mWindow->get_render());
}

void LevelDisplayer::undisplayLevel(Level& level){
	mCamera.undisplayLevel();
    delete level.get_character()->getDisplayer();
    level.get_character()->set_displayer(NULL);
    //
    delete level.get_grid()->getDisplayer();
    level.get_grid()->set_displayer(NULL);
    //
    std::list<Monster*>::iterator it = level.get_monster_iterator();
    std::list<Monster*>::iterator end = level.get_monster_list_end();
    for (;it!=end;it++)
        {
            delete (*it)->getDisplayer();
            (*it)->set_displayer(NULL);
        }
    //
    deleteCellElemDisplayers(*level.get_grid());
    level.get_root_node()->remove_node();
}
