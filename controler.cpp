#include "controler.h"
#include "pandaFramework.h"
#include "command.h"


void error_message(string s)
{
    cout<<s<<endl;
}


CommandLauncher::CommandLauncher(KeyboardEvent key, Controler *controler, Command command):
m_key_event(key), m_controler(controler), m_command(command)
{}

KeyboardEvent CommandLauncher::get_key_event()
{ return m_key_event; }

void CommandLauncher::launch_command()
{m_controler->apply_command(m_command);}


CommandCanceler::CommandCanceler(KeyboardEvent key, Controler *controler, Command command)
:CommandLauncher(key, controler, command)
{}

void CommandCanceler::launch_command()
{m_controler->cancel_command(m_command);}

void launchCommand(const Event * theEvent, void * data)
{ ((CommandLauncher*)data)->launch_command(); }

Controler::Controler(KeyboardManager* km):m_character(NULL), m_last_update_time(0.)
{ initCommands(km); }

void Controler::initCommands(KeyboardManager* km)
{
    m_command_list.push_back(new CommandLauncher(MOVE_LEFT_KEY, this, MOVE_LEFT));
    m_command_list.push_back(new CommandLauncher(MOVE_RIGHT_KEY, this, MOVE_RIGHT));
    m_command_list.push_back(new CommandLauncher(MOVE_UP_KEY, this, MOVE_UP));
    m_command_list.push_back(new CommandLauncher(MOVE_DOWN_KEY, this, MOVE_DOWN));
    m_command_list.push_back(new CommandCanceler(MOVE_LEFT_STOP_KEY, this, MOVE_LEFT));
    m_command_list.push_back(new CommandCanceler(MOVE_RIGHT_STOP_KEY, this, MOVE_RIGHT));
	m_command_list.push_back(new CommandCanceler(MOVE_UP_STOP_KEY, this, MOVE_UP));
	m_command_list.push_back(new CommandCanceler(MOVE_DOWN_STOP_KEY, this, MOVE_DOWN));
    
    std::list<CommandLauncher*>::iterator it;
    for (it=m_command_list.begin(); it!=m_command_list.end();it++)
    {   
		km->register_key((*it)->get_key_event(), launchCommand,  (*it));
    }
    set_command_state(MOVE_LEFT, false);
    set_command_state(MOVE_RIGHT, false);
    set_command_state(MOVE_UP, false);
    set_command_state(MOVE_DOWN, false);
}

void Controler::set_command_state(Command command, bool state)
{
    m_command_state[command] = state;
}

bool Controler::get_command_state(Command command)
{
    return m_command_state[command];
}
void Controler::update(double current_time)
{
    if (m_character == NULL){
        return;
    }
    if (current_time<m_last_update_time+m_character->get_update_delay()){
        return;
    }
    if (!m_character->command_list_empty())
        {return; }
    else
        {
        std::map<Command, bool>::const_iterator it;
        for(it=m_command_state.begin();it!=m_command_state.end();it++)
            {
            if (it->second)
                {
                m_character->set_command(it->first);
                }
            } 
        }
    m_last_update_time = current_time;
}

Controler::~Controler()
{
    std::list<CommandLauncher*>::iterator it;
    for (it=m_command_list.begin(); it!=m_command_list.end();it++)
    {   
        delete *it;
    }  
    m_command_list.clear();
}

void Controler::apply_command(Command command)
{
    set_command_state(command, true);
    if (m_character!=NULL)
        { m_character->set_command(command); }
    else
        {return;}
}

void Controler::cancel_command(Command command)
{
    set_command_state(command, false);
    //if (m_character!=NULL)
        //{ 
        //if (m_character->get_command()==command)
            //{ m_character->set_command(STAY); }
        //}
    //else
        //{ error_message("NULL MainCharacter in controler."); }
}

void Controler::setMainCharacter(MainCharacter* mainCharacter){
    m_character = mainCharacter;
}

void Controler::removeMainCharacter(){
    m_character = NULL;
}
