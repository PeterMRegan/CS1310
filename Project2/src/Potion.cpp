#include "libtcod.hpp"
class Actor;
#include "Persistent.hpp"
#include "Attacker.hpp"
#include "Destructible.hpp"
#include "Ai.hpp"
#include "Pickable.hpp"
#include "Container.hpp"
#include "Potion.hpp"
#include "Actor.hpp"
#include "Gui.hpp"
#include "Map.hpp"
#include "Engine.hpp"

Healer::Healer(float amount) : amount(amount)
{
}

bool Healer::use(Actor *owner, Actor *wearer)
{
	if (wearer->destructible)
	{
		float amountHealed = wearer->destructible->heal(amount);
		if (amountHealed > 0)
		{
			engine.topGui->message(TCODColor::green, "You feel better!");
			return Pickable::use(owner,wearer);
		}
	}
	return false;
}

void Healer::load(TCODZip &zip)
{
	amount=zip.getFloat();
}

void Healer::save(TCODZip &zip)
{
	zip.putInt(HEALER);
	zip.putFloat(amount);
}
