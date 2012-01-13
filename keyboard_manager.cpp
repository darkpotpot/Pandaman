#include "keyboard_manager.h"

#define stringify( name ) # name

KeyboardManager::KeyboardManager(PandaFramework* framework)
{
	m_pFrameWork = framework;
	initKeys();
}

void KeyboardManager::initKeys()
{
	m_KeyboardEvents[SWITCH_CAMERA_KEY] = "c";
	m_KeyboardEvents[MOVE_LEFT_KEY] = "arrow_left";
	m_KeyboardEvents[MOVE_RIGHT_KEY] = "arrow_right";
	m_KeyboardEvents[MOVE_UP_KEY] = "arrow_up";
	m_KeyboardEvents[MOVE_DOWN_KEY] = "arrow_down";
	m_KeyboardEvents[MOVE_LEFT_STOP_KEY] = "arrow_left-up";
	m_KeyboardEvents[MOVE_RIGHT_STOP_KEY] = "arrow_right-up";
	m_KeyboardEvents[MOVE_UP_STOP_KEY] = "arrow_up-up";
	m_KeyboardEvents[MOVE_DOWN_STOP_KEY] = "arrow_down-up";
}

void KeyboardManager::register_key(KeyboardEvent event_name, EventHandler::EventCallbackFunction *function, void *data)
{
	m_pFrameWork->define_key(m_KeyboardEvents[event_name], stringify(event_name), function, data);
}

bool KeyboardManager::unregister_key(KeyboardEvent event_name)
{
	return m_pFrameWork->get_event_handler().remove_hooks(m_KeyboardEvents[event_name]);
}