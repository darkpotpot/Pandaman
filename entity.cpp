#include <iostream>

#include "entity.h"

using namespace std;

Entity::Entity():m_x(0), m_y(0)
{}

Entity::Entity(int x, int y):m_x(x), m_y(y)
{}

void Entity::update()
{
cout<<"Entity updating"<<endl;   
}