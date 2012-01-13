#ifndef LEVEL_DISPLAYER_H
#define LEVEL_DISPLAYER_H

#include "pandaFramework.h"

#include "level.h"
#include "model_manager.h"
#include "world_camera.h"
#include "keyboard_manager.h"


class LevelDisplayer{
    public:
        LevelDisplayer(WindowFramework* window, PandaFramework* framework, KeyboardManager* km);
        void displayLevel(Level& level);
        void undisplayLevel(Level& level);
    private:
        WindowFramework* mWindow;
        ModelManager mModelManager;
        WorldCamera mCamera;
};

#endif
