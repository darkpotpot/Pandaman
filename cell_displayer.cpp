#include "cell_displayer.h"
#include "drawing_helpers.h"
#include "global.h"

CellElemDisplayer::CellElemDisplayer(int x, int y, string model_name, WindowFramework *window, PandaFramework *framework)
:m_model_name(model_name),m_window(window), m_framework(framework)
{
     m_drawing = window->load_model(framework->get_models(), model_name);
     m_drawing.reparent_to(m_window->get_render());
     float ratio = (float) CASE_RATIO;
     scale_at_size(ratio, ratio, ratio, &m_drawing);
     float posX = (ratio * x) + ratio / 2.;
     float posY = (ratio * y) + ratio / 2.;
     m_drawing.set_pos( posX, posY, 0.);
}


void initCellElemDisplayers(Grid& grid, WindowFramework *window, PandaFramework *framework){
    for (int i=0; i < grid.mHeight; i++){
        for (int j=0; j < grid.mWidth; j++){
            vector<CellElem*> elems = grid.getCellElems(i, j);
            vector<CellElem*>::iterator it;
            for ( it=elems.begin() ; it < elems.end(); it++ ){
                switch((*it)->getType()){
                    case WALL:
                        (*it)->set_displayer(new CellElemDisplayer(i, j, "resources/meshes/wall.egg", window, framework));
                        break;
                }
            }
        }
    }
}
