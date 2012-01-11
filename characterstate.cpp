#include "characterstate.h"

CharacterState::CharacterState(CharStateType state_type, int nb_turn)
:mRemainingTurn(nb_turn), mStateType(state_type)
{}

void CharacterState::update()
{mRemainingTurn=mRemainingTurn-1;}

bool CharacterState::finished()
{return mRemainingTurn<=0;}

bool CharacterState::isStateType(CharStateType stateType)
{return (mStateType==stateType);}