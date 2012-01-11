#ifndef BONUS_H
#define BONUS_H
#include "cell.h"
#include "characterstate.h"

class Bonus:public CellElem{
    public:
        Bonus(int x, int y, int nb_turn, CharStateType bonusType);
        virtual const CellElemType getType(){return BONUS;};
        virtual int get_x(){return m_x;};
        virtual int get_y(){return m_y;};
        CharStateType getBonusType(){return mBonusType;};
        int getNbTurn(){return mNbTurn;};
    private:
        int m_x;
        int m_y;
        int mNbTurn;
        CharStateType mBonusType;


};

#endif