#ifndef LEVEL_INTERFACE_H
#define LEVEL_INTERFACE_H

#include "pandaFramework.h"


class LevelInterface{
public:
	LevelInterface(WindowFramework* window);
	void hide();
	void show();
	void set_lifes(int dLifes);
private:
	NodePath m_interface;
	PT(TextNode) m_lifes;
};

#endif