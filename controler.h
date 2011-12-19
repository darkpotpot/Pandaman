#ifndef Controler_H
#define Controler_H
#include "pandaFramework.h"
#include "character.h"
#include <map>

class CommandLauncher;

class Controler
{
public:
    Controler(PandaFramework &framework);
    ~Controler();
    void moveLeft(const Event * theEvent, void * data);
    void apply_command(Command command);
    void cancel_command(Command command);
    void update();
    void setMainCharacter(MainCharacter* mainCharacter);
    void removeMainCharacter();
private:
    void set_command_state(Command command, bool state);
    bool get_command_state(Command command);
    
    void initCommands(PandaFramework &framework);
    MainCharacter *m_character;
    std::list<CommandLauncher*> m_command_list;
    std::map<Command, bool> m_command_state;
    
};

class CommandLauncher{
    public:
        CommandLauncher(string key, string name, Controler *controler, Command command);
        virtual void launch_command();
        string get_name();
        string get_key();

    protected:
        Controler *m_controler;
        Command m_command;
        
    private:
        string m_name;
        string m_key;
    };
    
class CommandCanceler:public CommandLauncher{
    public:
        CommandCanceler(string key, string name, Controler *controler, Command command);
        virtual void launch_command();
    
    };
#endif
