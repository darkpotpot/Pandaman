#include "level_displayer.h"
#include "heightfield_displayer.h"
#include "cell_displayer.h"
#include "character_displayer.h"


LevelDisplayer::LevelDisplayer(WindowFramework* window, PandaFramework* framework):mWindow(window), mFramework(framework),mModelManager(ModelManager(window, framework)), mCamera(WorldCamera(window)){
}


void LevelDisplayer::displayLevel(Level& level){
    level.rootNode = NodePath("level");
    level.grid.set_displayer(new HeightfieldDisplayer(&level.grid, &level.rootNode));
    level.panda.set_displayer(new CharacterDisplayer("panda-model", &level.rootNode, &mModelManager));
    initCellElemDisplayers(level.grid, mWindow, &mModelManager);
    mCamera.seeAll(level.grid);
    //
    //
    level.rootNode.reparent_to(mWindow->get_render());
}
