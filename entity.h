#ifndef Entity_H
#define Entity_H

class Entity
{
public:
    Entity();
    Entity(int x, int y);
    void update();
    //move to...
    //m_displayer.update(this)
    int m_x;
    int m_y;
};

#endif