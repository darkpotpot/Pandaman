#ifndef Controler_H
#define Controler_H
#include "pandaFramework.h"
#include "character.h"

class CommandLauncher;

class Controler
{
public:
    Controler(PandaFramework &framework);
    Controler(PandaFramework &framework, Character* character);
    void moveLeft(const Event * theEvent, void * data);
    void apply_command(Command command);
private:
    void initCommands(PandaFramework &framework);
    Character *m_character;
    std::list<CommandLauncher> m_command_list;
    
};

class CommandLauncher{
    public:
        CommandLauncher(string key, string name, Controler *controler, Command m_command);
        void launch_command();
        string get_name();
        string get_key();

    private:
        Controler *m_controler;
        Command m_command;
        string m_name;
        string m_key;
    };
#endif