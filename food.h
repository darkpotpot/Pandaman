#ifndef FOOD_H
#define FOOD_H
#include "cell.h"

class Food:public CellElem{
    public:
        Food();
        Food(int x, int y);
        ~Food();
        virtual const CellElemType getType(){return FOOD;};
        virtual bool blocks(){return false;};
        virtual int get_x(){return m_x;};
        virtual int get_y(){return m_y;};
        static bool noMoreFood();
    private:
        static int nb_food;
        int m_x;
        int m_y;

};

#endif