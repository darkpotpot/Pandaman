#include "model_manager.h"


ModelManager::ModelManager(WindowFramework* window, PandaFramework* framework){
    mWindow = window;
    mFramework = framework;
}


NodePath ModelManager::loadModel(string model_name){
    map<string, NodePath>::iterator it = mModels.find(model_name);
    if (it == mModels.end()){
        mModels[model_name] = mWindow->load_model(mFramework->get_models(), model_name);
    }
    return mModels.find(model_name)->second.copy_to(NULL);
}
