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

MainCharacter::MainCharacter():Entity()
{}

MainCharacter::MainCharacter(Grid *grid):Entity(grid)
{}

MainCharacter::MainCharacter(int x, int y, Grid *grid):Entity(x, y, grid)
{}

void MainCharacter::update()
{
    int x_dir = 0;
    int y_dir = 0;
    Command last_command = STAY;
    if (!m_last_command.empty())
    {
        last_command = m_last_command.front();
        m_last_command.pop_front();
    }
    
    switch(last_command)
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
    if (m_last_command.size()>=2)
        {
            m_last_command.pop_back();
        }
        
    m_last_command.push_back(command);
    return 0;
}

Command MainCharacter::get_command()
{
    return m_last_command.back();
}

bool MainCharacter::command_list_empty()
{
return m_last_command.empty();
}
