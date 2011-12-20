#include "cell_displayer.h"
#include "drawing_helpers.h"
#include "entity_displayer.h"
#include "character_displayer.h"
#include "global.h"

CellElemDisplayer::CellElemDisplayer(int x, int y, string model_name, NodePath *parentNode, ModelManager* model_manager)
{
     mDrawing = model_manager->loadModel(model_name);
     mDrawing.reparent_to(*parentNode);
     float ratio = (float) CASE_RATIO;
     scale_at_size(ratio, ratio, ratio, &mDrawing);
     float posX = (ratio * x) + ratio / 2.;
     float posY = (ratio * y) + ratio / 2.;
     mDrawing.set_pos( posX, posY, 0.);
}


void initCellElemDisplayers(Grid& grid, NodePath *parentNode, ModelManager* model_manager){
    for (int i=0; i < grid.mHeight; i++){
        for (int j=0; j < grid.mWidth; j++){
            list<CellElem*> elems = grid.getCellElems(i, j);
            list<CellElem*>::iterator it;
            for ( it=elems.begin() ; it != elems.end(); it++ ){
                switch((*it)->getType()){
                    case WALL:
                        (*it)->set_displayer(new CellElemDisplayer(i, j, "resources/meshes/wall.egg", parentNode, model_manager));
                        break;
                    case ENTITY:
                        (*it)->set_displayer(new EntityDisplayer("smiley", parentNode, model_manager, 5, LPoint3f(2,2,2)));
                        break;
                    case CHARACTER:
                        (*it)->set_displayer(new CharacterDisplayer("panda-model", parentNode, model_manager));
                        break;
                }
            }
        }
    }
}
