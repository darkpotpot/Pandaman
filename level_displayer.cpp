#include "level_displayer.h"
#include "heightfield_displayer.h"
#include "cell_displayer.h"

LevelDisplayer::LevelDisplayer(WindowFramework* window, PandaFramework* framework):mWindow(window), mFramework(framework),mModelManager(ModelManager(window, framework)), mCamera(WorldCamera(window)){
}


void LevelDisplayer::displayLevel(Level& level){
    level.get_grid()->set_displayer(new HeightfieldDisplayer(level.get_grid(), level.get_root_node()));
    //
    initCellElemDisplayers(*level.get_grid(), level.get_root_node(), &mModelManager);
    mCamera.seeAll(*level.get_grid());
    level.get_root_node()->reparent_to(mWindow->get_render());
}

void LevelDisplayer::undisplayLevel(Level& level){
    level.get_root_node()->remove_node();
}
