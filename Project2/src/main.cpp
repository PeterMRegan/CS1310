#include <unistd.h>
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

Engine engine(80,60);

int main()
{
	engine.load();
	while (!TCODConsole::isWindowClosed())
	{
		usleep(100000); //check every tenth of a second
		engine.update();
		engine.render();
		TCODConsole::flush();
	}
	engine.save();
	return 0;
}
