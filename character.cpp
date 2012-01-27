#include <string>
#include <iostream>

#include "entity.h"
#include "character.h"
#include "command.h"
#include "characterstate.h"
#include <iostream>
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

MainCharacter::~MainCharacter(){
    CharacterState* state;
    while (!m_states.empty())
    {
        state = m_states.front();
        m_states.remove(state);
        delete state;
    }
}

void MainCharacter::update(EventManager& event_manager)
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

    if (hasState(DRUNK))
    {
        x_dir = -x_dir;
        y_dir = -y_dir;
    }

    if (!(x_dir==0 && y_dir==0))
    {
        int new_x = m_x+x_dir;
        int new_y = m_y+y_dir;
        Entity::move_to_ifp(new_x, new_y, event_manager);
    }
    Entity::update(event_manager);
    updateStates();

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


void MainCharacter::updateStates()
{
    list<CharacterState*> to_remove;
    list<CharacterState*>::iterator it;
    for (it=m_states.begin(); it!=m_states.end();it++)
    {
        (*it)->update();
        if((*it)->finished())
        {
            to_remove.push_back(*it);
        }
    }
    CharacterState* state;
    while (!to_remove.empty())
    {
        state = to_remove.front();
        m_states.remove(state);
        to_remove.remove(state);
        delete state;
    }
}

void MainCharacter::addState(CharStateType state, int nb_turn)
{
    CharacterState* char_state = new CharacterState(state, nb_turn);
    m_states.push_back(char_state);
}

bool MainCharacter::hasState(CharStateType state)
{
    std::list<CharacterState*>::iterator it;
    for (it = m_states.begin(); it!=m_states.end(); it++)
    {
        if ((*it)->isStateType(state))
        {return true;}
    }
    return false;
}