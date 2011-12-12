#ifndef Character_H
#define Character_H
#include "entity.h"
#include "command.h"

class Character:public Entity{
public:
    Character();
    Character(Grid *grid);
    Character(int x, int y, Grid *grid);
    virtual void update();
    int set_command(Command command);
    
private:
    Command m_last_command;
};

#endif