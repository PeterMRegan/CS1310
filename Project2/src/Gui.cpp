#include <stdarg.h>
#include <stdio.h>
#include <string>
#include "main.hpp"

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
	const char *name = engine.player->name;
	con->setDefaultForeground(TCODColor::lightGrey);
	con->print(0,0,"Name:%s",name);

	//draw the players hp
	con->setDefaultForeground(TCODColor::red);
	con->print(0,2,"HP:%d/%d",(int)engine.player->destructible->hp,(int)engine.player->destructible->maxHp);

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