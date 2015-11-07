#include "main.hpp"
#include <math.h>
#include <iostream>

Actor::Actor(int x, int y, int ch, const char *name, const TCODColor &col) : x(x),y(y),ch(ch),col(col),name(name),blocks(true),attacker(NULL),destructible(NULL),ai(NULL),pickable(NULL),container(NULL)
{
}

Actor::~Actor()
{
	if (attacker) delete attacker;
	if (destructible) delete destructible;
	if (ai) delete ai;
	if (pickable) delete pickable;
	if (container) delete container;
}

void Actor::render() const
{
	TCODConsole::root->setChar(x,y+MAP_OFFSET,ch);
	TCODConsole::root->setCharForeground(x,y+MAP_OFFSET,col);
}

void Actor::update()
{
	if (ai) ai->update(this);
}

float Actor::getDistance(int cx, int cy) const
{
	int dx=x-cx;
	int dy=y-cy;
	return sqrtf(dx*dx+dy*dy);
}

void Actor::save(TCODZip &zip)
{
	zip.putInt(x);
	zip.putInt(y);
	zip.putInt(ch);
	zip.putColor(&col);
	zip.putString(name);
	zip.putInt(blocks);
	zip.putInt(attacker!=NULL);
	zip.putInt(destructible!=NULL);
	zip.putInt(ai!=NULL);
	zip.putInt(pickable!=NULL);
	zip.putInt(container!=NULL);
	if (attacker) attacker->save(zip);
	if (destructible) destructible->save(zip);
	if (ai) ai->save(zip);
	if (pickable) pickable->save(zip);
	if (container) container->save(zip);
}

void Actor::load(TCODZip &zip)
{
	std::cout << "getting x" << std::endl;
	x=zip.getInt();
	std::cout << "getting y" << std::endl;
	y=zip.getInt();
	std::cout << "getting ch" << std::endl;
	ch=zip.getInt();
	std::cout << "getting col" << std::endl;
	col=zip.getColor();
	std::cout << "getting name" << std::endl;
	name=strdup(zip.getString());
	std::cout << "getting blocking info" << std::endl;
	blocks=zip.getInt();
	std::cout << "getting attacker" << std::endl;
	bool hasAttacker=zip.getInt();
	std::cout << "getting destructible" << std::endl;
	bool hasDestructible=zip.getInt();
	std::cout << "getting ai" << std::endl;
	bool hasAi=zip.getInt();
	std::cout << "getting pickable" << std::endl;
	bool hasPickable=zip.getInt();
	std::cout << "getting container" << std::endl;
	bool hasContainer=zip.getInt();
	if (hasAttacker)
	{
		std::cout << "setting attacker" << std::endl;
		attacker = new Attacker(0.0f);
		attacker->load(zip);
	}
	if (hasDestructible)
	{
		std::cout << "setting destructible" << std::endl;
		destructible = Destructible::create(zip);
	}
	std::cout << "test" << std::endl;
	if (hasAi)
	{
		std::cout << "setting ai" << std::endl;
		ai = Ai::create(zip);
	}
	if (hasPickable)
	{
		std::cout << "setting pickable" << std::endl;
		pickable = Pickable::create(zip);
	}
	if (hasContainer)
	{
		container = new Container(0);
		container->load(zip);
	}
}
