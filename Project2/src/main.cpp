#include <unistd.h>
#include "libtcod.hpp"
#include "Actor.hpp"
#include "Engine.hpp"

Engine engine(80,60);

int main()
{
	while (!TCODConsole::isWindowClosed() && engine.gameStatus!=Engine::DEFEAT)
	{
		usleep(100000); //check every tenth of a second
		engine.update();
		engine.render();
		TCODConsole::flush();
	}
	return 0;
}
