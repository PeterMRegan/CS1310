#include <stdio.h>
#include "libtcod.hpp"
class Actor;
#include "Persistent.hpp"
#include "Attacker.hpp"
#include "Destructible.hpp"
#include "Ai.hpp"
#include "Pickable.hpp"
#include "Container.hpp"
#include "Actor.hpp"
#include "Gui.hpp"
#include "Map.hpp"
#include "Engine.hpp"

Attacker::Attacker(float power) : power(power)
{
}

void Attacker::attack(Actor *owner, Actor *target)
{
	if (target->destructible && !target->destructible->isDead())
	{
		if (power - target->destructible->defense > 0)
		{
			engine.topGui->message(owner==engine.player?TCODColor::red : TCODColor::lightGrey, "%s attacks %s for %g hit points.", owner->name, target->name, power - target->destructible->defense);
		}
		else
		{
			engine.topGui->message(TCODColor::lightGrey, "%s attacks %s but it has no effect!", owner->name, target->name);
		}
		target->destructible->takeDamage(target,power);
	}
	else
	{
		engine.topGui->message(TCODColor::lightGrey, "%s attacks %s in vain.", owner->name, target->name);
	}
}

void Attacker::load(TCODZip &zip)
{
	power=zip.getFloat();
}

void Attacker::save(TCODZip &zip)
{
	zip.putFloat(power);
}
