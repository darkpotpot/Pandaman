#include "controler.h"
#include "pandaFramework.h"
#include "command.h"


void error_message(string s)
{
    cout<<s<<endl;
}


CommandLauncher::CommandLauncher(string key, string name, Controler *controler, Command command):
m_name(name), m_key(key), m_controler(controler), m_command(command)
{}

string CommandLauncher::get_name()
{ return m_name; }

string CommandLauncher::get_key()
{ return m_key; }

void CommandLauncher::launch_command()
{m_controler->apply_command(m_command);}


CommandCanceler::CommandCanceler(string key, string name, Controler *controler, Command command)
:CommandLauncher(key, name, controler, command)
{}

void CommandCanceler::launch_command()
{m_controler->cancel_command(m_command);}

void launchCommand(const Event * theEvent, void * data)
{ ((CommandLauncher*)data)->launch_command(); }

Controler::Controler(PandaFramework &framework):m_character(NULL)
{ initCommands(framework); }

Controler::Controler(PandaFramework &framework, MainCharacter* character):m_character(character)
{ initCommands(framework); }

void Controler::initCommands(PandaFramework &framework)
{
    m_command_list.push_back(new CommandLauncher("arrow_left","left", this, MOVE_LEFT));
    m_command_list.push_back(new CommandLauncher("arrow_right","right", this, MOVE_RIGHT));
    m_command_list.push_back(new CommandLauncher( "arrow_up","up", this, MOVE_UP));
    m_command_list.push_back(new CommandLauncher("arrow_down","down", this, MOVE_DOWN));
    //m_command_list.push_back(CommandLauncher("arrow_left-repeat","left", this, MOVE_LEFT));
    //m_command_list.push_back(CommandLauncher("arrow_right-repeat","right", this, MOVE_RIGHT));
    //m_command_list.push_back(CommandLauncher( "arrow_up-repeat","up", this, MOVE_UP));
    //m_command_list.push_back(CommandLauncher("arrow_down-repeat","down", this, MOVE_DOWN));
    m_command_list.push_back(new CommandCanceler("arrow_left-up","left_stop", this, MOVE_LEFT));
    m_command_list.push_back(new CommandCanceler("arrow_right-up","right_stop", this, MOVE_RIGHT));
    m_command_list.push_back(new CommandCanceler( "arrow_up-up","up_stop", this, MOVE_UP));
    m_command_list.push_back(new CommandCanceler("arrow_down-up","down_stop", this, MOVE_DOWN));
    
    std::list<CommandLauncher*>::iterator it;
    for (it=m_command_list.begin(); it!=m_command_list.end();it++)
    {   
        framework.define_key((*it)->get_key(), (*it)->get_name(), launchCommand,  (*it));
    }
    //framework.define_key("q","left", launchCommand,  &(m_command_list.back()));

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
    if (m_character!=NULL)
        { m_character->set_command(command); }
    else
        { error_message("NULL MainCharacter in controler."); }
}

void Controler::cancel_command(Command command)
{
    if (m_character!=NULL)
        { 
        if (m_character->get_command()==command)
            { m_character->set_command(STAY); }
        }
    else
        { error_message("NULL MainCharacter in controler."); }
}