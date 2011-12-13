#ifndef Displayable_H
#define Displayable_H
#include "displayer.h"

class Displayer;

class Displayable
{
public:
    Displayable();
    virtual int get_x();
    virtual int get_y();
    void set_displayer(Displayer * displayer);
protected:
    Displayer * m_displayer;
};

#endif
