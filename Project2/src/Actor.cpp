#include "main.hpp"

Actor::Actor(int x, int y, int ch, const char *name, const TCODColor &col) : x(x),y(y),ch(ch),col(col),name(name),blocks(true),attacker(NULL),destructible(NULL),ai(NULL)
{
}

void Actor::render() const
{
	TCODConsole::root->setChar(x,y+5,ch);
	TCODConsole::root->setCharForeground(x,y+5,col);
}

void Actor::update()
{
	if (ai) ai->update(this);
}
