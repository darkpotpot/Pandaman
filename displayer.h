#ifndef Displayer_H
#define Displayer_H

#include "displayable.h"

class Entity;

class Displayer
{
public:
    Displayer();
    virtual int update(Displayable* entity);
};

#endif