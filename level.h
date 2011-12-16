#ifndef LEVEL_H
#define LEVEL_H

#include "grid.h"
#include "character.h"
#include "simu.h"

struct Level{
    Grid grid;
    MainCharacter panda;
    NodePath rootNode;
    SimulationTask simu;
};

#endif
