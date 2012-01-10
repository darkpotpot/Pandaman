#include "food.h"

int Food::nb_food = 0;
Food::Food():m_x(0), m_y(0)
{ nb_food = nb_food+1; }

Food::Food(int x, int y):m_x(x), m_y(y)
{ nb_food = nb_food+1; }

Food::~Food()
{
    nb_food = nb_food-1;

}