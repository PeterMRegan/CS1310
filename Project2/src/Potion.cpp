#include "main.hpp"

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
