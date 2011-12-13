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

MainCharacter::MainCharacter():Entity(), m_last_command(STAY)
{}

MainCharacter::MainCharacter(Grid *grid):Entity(grid), m_last_command(STAY)
{}

MainCharacter::MainCharacter(int x, int y, Grid *grid):Entity(x, y, grid), m_last_command(STAY)
{}

void MainCharacter::update()
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
           x_dir = -1;
           break;
        }
        case MOVE_RIGHT:
        {
           x_dir = +1;
           break;
        }
        case MOVE_UP:
        {
           y_dir=+1;
           break;
        }
           case MOVE_DOWN:
        {
           y_dir = -1;
           break;
        }    
    }
    m_last_command = STAY;
    if (!(x_dir==0 && y_dir==0))
    {
        int new_x = m_x+x_dir;
        int new_y = m_y+y_dir;
        Entity::move_to_ifp(new_x, new_y );
    }
    Entity::update();

}

int MainCharacter::set_command(Command command)
{
    m_last_command = command;
    return 0;
}