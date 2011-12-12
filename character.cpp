#include <string>
#include <iostream>

#include "entity.h"
#include "character.h"
#include "command.h"

using namespace std;

int print_message(string s)
{
    cout<<s<<endl;
    return 0;
}

Character::Character():Entity(), m_last_command(STAY)
{}

Character::Character(Grid *grid):Entity(grid), m_last_command(STAY)
{}

Character::Character(int x, int y, Grid *grid):Entity(x, y, grid), m_last_command(STAY)
{}

void Character::update()
{
    int x_dir = 0;
    int y_dir = 0;
    switch(m_last_command)
    {
        case STAY:
        {
           break;
        }
        case MOVE_LEFT:
        {
           print_message("MOVE_LEFT");
           break;
        }
        case MOVE_RIGHT:
        {
           print_message("MOVE_RIGHT");
           break;
        }
        case MOVE_UP:
        {
           print_message("MOVE_UP");
           break;
        }
           case MOVE_DOWN:
        {
           print_message("MOVE_DOWN");
           break;
        }    
    }
    m_last_command = STAY;
    
}

int Character::set_command(Command command)
{
    m_last_command = command;
    return 0;
}