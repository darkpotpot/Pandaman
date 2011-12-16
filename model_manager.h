#ifndef ModelManager_H
#define ModelManager_H

#include <string>
#include <map>
#include "windowFramework.h"
#include "pandaFramework.h"



class ModelManager{
    public:
        ModelManager(WindowFramework* window, PandaFramework* framework);
        NodePath loadModel(string model_name);
    private:
        WindowFramework* mWindow;
        PandaFramework* mFramework;
        std::map <string, NodePath> mModels;
};


#endif
