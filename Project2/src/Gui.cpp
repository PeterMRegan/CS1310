#include "main.hpp"

static const int PANEL_HEIGHT=7;

Gui::Gui(int yOffset):yOffset(yOffset)
{
}

Gui::~Gui()
{
	delete con;
}

void Gui::render()
{
	//clear the GUI console
	con->setDefaultBackground(TCODColor::black);
	con->clear;

	//blit the GUI console on the root console
	TCODConsole::blit(con,0,0,engine.screenWidth,PANEL_HEIGHT,TCODConsole::root,0,engine.screenHeight-PANELHEIGHT-yOffset)
}




