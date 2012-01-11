#ifndef CHARACTERSTATE_H
#define CHARACTERSTATE_H

enum CharStateType {INVICIBLE, FAST, DRUNK};

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