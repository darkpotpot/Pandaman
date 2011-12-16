#ifndef MonsterDisplayer_H
#define MonsterDisplayer_H

class MonsterDisplayer : public Displayer
{
public:
    MonsterDisplayer(string model_name, NodePath *parentNode, ModelManager *model_manager);
    virtual int update(Displayable* entity);    
};

#endif