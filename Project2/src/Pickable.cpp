#include "Actor.hpp"
#include "Potion.hpp"
#include "Scroll.hpp"
#include "Engine.hpp"

bool Pickable::pick(Actor *owner, Actor *wearer)
{
	if (wearer->container && wearer->container->add(owner))
	{
		engine.map->actors.remove(owner);
		return true;
	}
	return false;
}

bool Pickable::use(Actor *owner, Actor *wearer)
{
	if (wearer->container)
	{
		wearer->container->remove(owner);
		delete owner;
		return true;
	}
	return false;
}

void Pickable::drop(Actor *owner, Actor *wearer)
{
	if (wearer->container)
	{
		wearer->container->remove(owner);
		engine.map->actors.push(owner);
		engine.sendToBack(owner);
		owner->x=wearer->x;
		owner->y=wearer->y;
		engine.topGui->message(TCODColor::lightGrey,"%s drops a %s.",wearer->name,owner->name);
	}
}

Pickable *Pickable::create(TCODZip &zip)
{
	PickableType type=(PickableType)zip.getInt();
	Pickable *pickable=NULL;
	switch(type)
	{
		case HEALER : pickable=new Healer(0); break;
		case LIGHTNING_BOLT : pickable=new LightningBolt(0,0); break;
	}
	pickable->load(zip);
	return pickable;
}
