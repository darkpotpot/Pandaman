#ifndef WordlCamera_H
#define WordlCamera_H

#include "grid.h"
#include "keyboard_manager.h"
#include "entity_displayer.h"
#include "level.h"

class WorldCamera{
    public:
        WorldCamera(WindowFramework* window, KeyboardManager* km);
		void displayLevel(Level* level);
		void undisplayLevel();
		void switchCamera();
    private:
        NodePath mCamera;
		Level* m_level;
		KeyboardManager* m_pKeyboardManager;
		int m_CamType;
		void seeAll();
		void followDisplayable();
		void resetCamera();
};


#endif
