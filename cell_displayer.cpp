#include "cell_displayer.h"
#include "drawing_helpers.h"
#include "global.h"

CellElemDisplayer::CellElemDisplayer(int x, int y, string model_name, WindowFramework *window, ModelManager* model_manager)
{
     mDrawing = model_manager->loadModel(model_name);
     mDrawing.reparent_to(window->get_render());
     float ratio = (float) CASE_RATIO;
     scale_at_size(ratio, ratio, ratio, &mDrawing);
     float posX = (ratio * x) + ratio / 2.;
     float posY = (ratio * y) + ratio / 2.;
     mDrawing.set_pos( posX, posY, 0.);
}


void initCellElemDisplayers(Grid& grid, WindowFramework *window, ModelManager* model_manager){
    for (int i=0; i < grid.mHeight; i++){
        for (int j=0; j < grid.mWidth; j++){
            vector<CellElem*> elems = grid.getCellElems(i, j);
            vector<CellElem*>::iterator it;
            for ( it=elems.begin() ; it < elems.end(); it++ ){
                switch((*it)->getType()){
                    case WALL:
                        (*it)->set_displayer(new CellElemDisplayer(i, j, "resources/meshes/wall.egg", window, model_manager));
                        break;
                }
            }
        }
    }
}
