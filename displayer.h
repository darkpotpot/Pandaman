class Displayer
{
virtual int update(Entity& entity);
}

class CharacterDisplayer : public Displayer
{
virtual int update(Entity& entity);
}

