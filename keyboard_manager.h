#ifndef KEYBOARD_MANAGER_H
#define KEYBOARD_MANAGER_H

#include "pandaFramework.h"
#include <map>

enum KeyboardEvent
{
	SWITCH_CAMERA_KEY,
	MOVE_LEFT_KEY,
	MOVE_RIGHT_KEY,
	MOVE_UP_KEY,
	MOVE_DOWN_KEY,
	MOVE_LEFT_STOP_KEY,
	MOVE_RIGHT_STOP_KEY,
	MOVE_UP_STOP_KEY,
	MOVE_DOWN_STOP_KEY
};

class KeyboardManager{
	public:
		KeyboardManager(PandaFramework* framework);
		void register_key(KeyboardEvent kevent, EventHandler::EventCallbackFunction *function, void *data);
		bool unregister_key(KeyboardEvent kevent);
	private:
		PandaFramework* m_pFrameWork;
		map<KeyboardEvent, string> m_KeyboardEvents;

		void initKeys();
};

#endif