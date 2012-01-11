#ifndef CHARACTERSTATE_H
#define CHARACTERSTATE_H

enum CharStateType {INVINCIBLE, FAST, DRUNK, RANDOM}; //todo: voir avec Grom si c est bien un characterstatetype car ça sert pour les bonus

class CharacterState
{
    public:
        CharacterState(CharStateType state_type, int nb_turn);
        void update();
        bool finished();
        bool isStateType(CharStateType stateType);

    private:
        int mRemainingTurn;
        CharStateType mStateType;
};
#endif