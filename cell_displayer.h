#ifndef CellDisplayer_H
#define CellDisplayer_H

#include "cell.h"
#include "grid.h"
#include <string>
#include "windowFramework.h"
#include "model_manager.h"


class CellElemDisplayer:public Displayer{
    public:
        CellElemDisplayer(int x, int y, string model_name, NodePath* parentNode, ModelManager* model_manager);
    private:
        NodePath mDrawing;
};

void initCellElemDisplayers(Grid& grid, NodePath *parentNode, ModelManager* model_manager);
void deleteCellElemDisplayers(Grid& grid);

#endif
