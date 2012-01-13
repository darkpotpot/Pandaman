#include "keyboard_manager.h"
#include "tinyxml/tinyxml.h"

KeyboardEvent NameToEvent(string event_name)
{
	if (event_name == string("SWITCH_CAMERA_KEY"))
		return SWITCH_CAMERA_KEY;
	else if (event_name == string("MOVE_LEFT_KEY"))
		return MOVE_LEFT_KEY; 
	else if (event_name == string("MOVE_RIGHT_KEY"))
		return MOVE_RIGHT_KEY;
	else if (event_name == string("MOVE_UP_KEY"))
		return MOVE_UP_KEY;
	else if (event_name == string("MOVE_DOWN_KEY"))
		return MOVE_DOWN_KEY;
	else
	{
		assert (false);
		return SWITCH_CAMERA_KEY;
	}
}

KeyboardManager::KeyboardManager(PandaFramework* framework)
{
	m_pFrameWork = framework;
	initKeys();
}

void KeyboardManager::initKeys()
{
	TiXmlDocument doc;
	bool loadOkay = doc.LoadFile("resources\\input.xml");
    assert (loadOkay);
    TiXmlHandle levelHandle(&doc);
    TiXmlHandle mapHandle = levelHandle.FirstChild("keys");
    TiXmlElement* child = mapHandle.FirstChild().ToElement();
    for(child; child; child=child->NextSiblingElement())
    {
		m_KeyboardEvents[NameToEvent(child->Attribute("name"))] = child->Attribute("key");
    }
	m_KeyboardEvents[MOVE_LEFT_STOP_KEY] = m_KeyboardEvents[MOVE_LEFT_KEY] + "-up";
	m_KeyboardEvents[MOVE_RIGHT_STOP_KEY] = m_KeyboardEvents[MOVE_RIGHT_KEY] + "-up";
	m_KeyboardEvents[MOVE_UP_STOP_KEY] = m_KeyboardEvents[MOVE_UP_KEY] + "-up";
	m_KeyboardEvents[MOVE_DOWN_STOP_KEY] = m_KeyboardEvents[MOVE_DOWN_KEY] + "-up";
}

void KeyboardManager::register_key(KeyboardEvent kevent, EventHandler::EventCallbackFunction *function, void *data)
{
	m_pFrameWork->define_key(m_KeyboardEvents[kevent], m_KeyboardEvents[kevent], function, data);
}

bool KeyboardManager::unregister_key(KeyboardEvent kevent)
{
	return m_pFrameWork->get_event_handler().remove_hooks(m_KeyboardEvents[kevent]);
}