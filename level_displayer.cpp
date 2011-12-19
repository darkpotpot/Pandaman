#include "level_displayer.h"
#include "heightfield_displayer.h"
#include "cell_displayer.h"
#include "character_displayer.h"
#include "entity_displayer.h"


LevelDisplayer::LevelDisplayer(WindowFramework* window, PandaFramework* framework):mWindow(window), mFramework(framework),mModelManager(ModelManager(window, framework)), mCamera(WorldCamera(window)){
}


void LevelDisplayer::displayLevel(Level& level){
    level.set_root_node(new NodePath("level"));
    level.get_grid()->set_displayer(new HeightfieldDisplayer(level.get_grid(), level.get_root_node()));
    level.get_character()->set_displayer(new CharacterDisplayer("panda-model", level.get_root_node(), &mModelManager));
    //
    std::list<Monster*>::iterator it = level.get_monster_iterator();
    std::list<Monster*>::iterator end = level.get_monster_list_end();
    for (;it!=end;it++)
        {
            (*it)->set_displayer(new EntityDisplayer("smiley", level.get_root_node(), &mModelManager, 5, LPoint3f(2,2,2)));
        }
    //.
    initCellElemDisplayers(*level.get_grid(), mWindow, &mModelManager);
    mCamera.seeAll(*level.get_grid());
    //
    //
    level.get_root_node()->reparent_to(mWindow->get_render());
}
