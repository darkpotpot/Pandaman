#ifndef MainCharacter_H
#define MainCharacter_H
#include "entity.h"
#include "command.h"
#include <list>
#include "event_manager.h"

class MainCharacter:public Entity{
public:
    MainCharacter();
    MainCharacter(Grid *grid);
    MainCharacter(int x, int y, Grid *grid);
    virtual const CellElemType getType(){return CHARACTER;};
    virtual void update(EventManager& event_manager);
    int set_command(Command command);
    bool command_list_empty();
    Command get_command();
    
private:
    std::list<Command> m_last_command;
};

#endif