#ifndef Controler_H
#define Controler_H
#include "keyboard_manager.h"
#include "character.h"
#include <map>

class CommandLauncher;

class Controler
{
public:
    Controler(KeyboardManager* km);
    ~Controler();
    void moveLeft(const Event * theEvent, void * data);
    void apply_command(Command command);
    void cancel_command(Command command);
    void update(double current_time);
    void setMainCharacter(MainCharacter* mainCharacter);
    void removeMainCharacter();
private:
    void set_command_state(Command command, bool state);
    bool get_command_state(Command command);
    
    void initCommands(KeyboardManager* km);
    MainCharacter *m_character;
    std::list<CommandLauncher*> m_command_list;
    std::map<Command, bool> m_command_state;
    double m_last_update_time;
    
};

class CommandLauncher{
    public:
        CommandLauncher(KeyboardEvent key, Controler *controler, Command command);
        virtual void launch_command();
        KeyboardEvent get_key_event();

    protected:
        Controler *m_controler;
        Command m_command;
        
    private:
        KeyboardEvent m_key_event;
    };
    
class CommandCanceler:public CommandLauncher{
    public:
        CommandCanceler(KeyboardEvent key, Controler *controler, Command command);
        virtual void launch_command();
    
    };
#endif
