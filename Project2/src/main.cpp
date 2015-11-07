#include <unistd.h>
#include "main.hpp"

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
