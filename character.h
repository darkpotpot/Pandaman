#ifndef MainCharacter_H
#define MainCharacter_H
#include "entity.h"
#include "command.h"

class MainCharacter:public Entity{
public:
    MainCharacter();
    MainCharacter(Grid *grid);
    MainCharacter(int x, int y, Grid *grid);
    virtual void update();
    int set_command(Command command);
    Command get_command();
    
private:
    Command m_last_command;
};

#endif