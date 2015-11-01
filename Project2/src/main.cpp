#include <unistd.h>
#include "main.hpp"

Engine engine(80,60);

int main()
{
	while (!TCODConsole::isWindowClosed())
	{
		usleep(100000); //check every tenth of a second
		engine.update();
		engine.render();
		TCODConsole::flush();
	}
	return 0;
}
