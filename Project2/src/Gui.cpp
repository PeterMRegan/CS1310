#include <stdarg.h>
#include <stdio.h>
#include <string>
#include "Actor.hpp"
#include "Engine.hpp"

static const int PANEL_HEIGHT=7;
static const int MSG_HEIGHT=PANEL_HEIGHT-1;

Gui::Gui(int yOffset):yOffset(yOffset)
{
	con = new TCODConsole(engine.screenWidth,PANEL_HEIGHT);
}

Gui::~Gui()
{
	delete con;
	log.clearAndDelete();
}

void Gui::renderLog()
{
	//clear the GUI console
	con->setDefaultBackground(TCODColor::black);
	con->clear();

	//draw the message log
	int y=1;
	float colorCoef=0.4f;
	for (Message **i=log.begin(); i!=log.end(); i++)
	{
		Message *message=*i;
		con->setDefaultForeground(message->col * colorCoef);
		con->print(0,y,message->text);
		y++;
		if (colorCoef < 1.0f)
		{
			colorCoef+=0.3f;
		}
	//blit the GUI console on the root console
	TCODConsole::blit(con,0,0,engine.screenWidth,PANEL_HEIGHT,TCODConsole::root,0,engine.screenHeight-PANEL_HEIGHT-yOffset);
	}
}

void Gui::renderStatus()
{
	//clear the GUI console
	con->setDefaultBackground(TCODColor::black);
	con->clear();

	//draw the players name
	con->setDefaultForeground(TCODColor::lightGrey);
	con->print(0,0,"Name:%s",engine.player->name);

	//draw the dungeon level
	con->setDefaultForeground(TCODColor::white);
	con->print(60,0,"Dungeon level %d",engine.level);

	//draw the players hp
	con->setDefaultForeground(TCODColor::red);
	con->print(0,2,"HP:%d/%d",(int)engine.player->destructible->hp,(int)engine.player->destructible->maxHp);

	//draw the number of monsters remaining
//	con->setDefaultForeground(TCODColor::darkSea);
//	con->print(0,4,"Monsters remaining:%d",(int)engine.monsters.size());

	//blit the GUI console on the root console
	TCODConsole::blit(con,0,0,engine.screenWidth,PANEL_HEIGHT,TCODConsole::root,0,engine.screenHeight-PANEL_HEIGHT-yOffset);
}

Gui::Message::Message(const char *text, const TCODColor &col) : text(strdup(text)), col(col)
{
}

Gui::Message::~Message()
{
	free(text);
}

void Gui::message(const TCODColor &col, const char *text, ...)
{
	//build the text
	va_list ap;
	char buf[128];
	va_start(ap,text);
	vsprintf(buf,text,ap);
	va_end(ap);
	char *lineBegin=buf;
	char *lineEnd;
	do
	{
		//make room for the new message
		if (log.size() == MSG_HEIGHT)
		{
			Message *toRemove=log.get(0);
			log.remove(toRemove);
			delete toRemove;
		}
		//detect end of the line
		lineEnd=strchr(lineBegin,'\n');
		if (lineEnd)
		{
			*lineEnd='\0';
		}
		//add a new message to the log
		Message *msg=new Message(lineBegin, col);
		log.push(msg);
		//go to next line
		lineBegin=lineEnd+1;
	} while (lineEnd);
}

void Gui::save(TCODZip &zip)
{
	zip.putInt(log.size());
	for (Message **i=log.begin(); i != log.end(); i++)
	{
		zip.putString((*i)->text);
		zip.putColor(&(*i)->col);
	}
}

void Gui::load(TCODZip &zip)
{
	int nbMessages=zip.getInt();
	while (nbMessages > 0)
	{
		const char *text=zip.getString();
		TCODColor col=zip.getColor();
		message(col,text);
		nbMessages--;
	}
}

void Gui::startMenu()
{
	static const int MENU_WIDTH=80;
	static const int MENU_HEIGHT=60;
	static TCODConsole con(MENU_WIDTH,MENU_HEIGHT);
	const char *menuMessage = "Welcome to Peter's C++ Project. Please choose how you would like to proceed.";
	bool inMenu = true;
	while (inMenu && !TCODConsole::isWindowClosed())
	{
		//display the menu frame
		con.setDefaultForeground(TCODColor(200,180,50));
		con.printFrame(0,0,MENU_WIDTH,MENU_HEIGHT,true,TCOD_BKGND_DEFAULT,"start menu");
		//display the menu options
		con.print(2,1,"%s",menuMessage);
		con.print(2,10,"(n) start a new game");
		con.print(2,15,"(l) load a saved game");
		//blit the inventory console on the root console
		TCODConsole::blit(&con,0,0,MENU_WIDTH,MENU_HEIGHT,TCODConsole::root, engine.screenWidth/2 - MENU_WIDTH/2, engine.screenHeight/2-MENU_HEIGHT/2);
		TCODConsole::flush();
		//wait for a key press
		TCOD_key_t key;
		TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS,&key,NULL,true);
		switch(key.c)
		{
			case 'n' : //start a new game
			{
				engine.init();
				inMenu = false;
			}
			break;
			case 'l' : //load a game
			{
				if (TCODSystem::fileExists("game.sav"))
				{
					engine.load();
					inMenu = false;
				}
				else
				{
					menuMessage = "There was no saved game to load.";
				}
			}
			break;
		}
	}
}
