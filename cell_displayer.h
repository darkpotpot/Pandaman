#ifndef CellDisplayer_H
#define CellDisplayer_H

#include "cell.h"
#include "grid.h"
#include <string>
#include "windowFramework.h"
#include "pandaFramework.h"

class CellElemDisplayer:public Displayer{
    public:
        CellElemDisplayer(int x, int y, string model_name, WindowFramework *window, PandaFramework *framework);
    private:
        NodePath m_drawing;
        WindowFramework *m_window;
        PandaFramework *m_framework;
        string m_model_name;
};

void initCellElemDisplayers(Grid& grid, WindowFramework *window, PandaFramework *framework);

#endif
