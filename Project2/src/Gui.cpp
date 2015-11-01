#include "main.hpp"

static const int PANEL_HEIGHT=7;
static const int MSG_HEIGHT=PANEL_HEIGHT-1;

Gui::Gui(int yOffset):yOffset(yOffset)
{
}

Gui::~Gui()
{
	delete con;
	log.clearAndDelete();
}

void Gui::render()
{
	//clear the GUI console
	con->setDefaultBackground(TCODColor::black);
	con->clear;

	//blit the GUI console on the root console
	TCODConsole::blit(con,0,0,engine.screenWidth,PANEL_HEIGHT,TCODConsole::root,0,engine.screenHeight-PANELHEIGHT-yOffset)

	//draw the message log
	int y=1;
	for (Message **i=log.begin(); i!=log.end(); i++)
	{
		Message *message=*i;
		con->
	}
}




