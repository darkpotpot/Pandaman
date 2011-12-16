#ifndef LEVEL_DISPLAYER_H
#define LEVEL_DISPLAYER_H

#include "pandaFramework.h"

#include "level.h"
#include "model_manager.h"
#include "world_camera.h"


class LevelDisplayer{
    public:
        LevelDisplayer(WindowFramework* window, PandaFramework* framework);
        void displayLevel(Level& level);
    private:
        WindowFramework* mWindow;
        PandaFramework* mFramework;
        ModelManager mModelManager;
        WorldCamera mCamera;
};

#endif
