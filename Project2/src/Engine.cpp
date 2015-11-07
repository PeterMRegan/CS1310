#include <iostream>
#include "main.hpp"

Engine::Engine(int screenWidth, int screenHeight):gameStatus(STARTUP),fovRadius(10),screenWidth(screenWidth),screenHeight(screenHeight)
{
	TCODConsole::initRoot(screenWidth,screenHeight,"libtcod C++ tutorial",false);
	topGui = new Gui(53);
	botGui = new Gui(0);
}

Engine::~Engine()
{
	actors.clearAndDelete();
	delete map;
	delete topGui;
	delete botGui;
}

void Engine::update()
{
	if (gameStatus == STARTUP) map->computeFov();
	gameStatus=IDLE;
	TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS,&lastKey,NULL);
	player->update();
	if (gameStatus == NEW_TURN)
	{
		for (Actor **i=actors.begin();i != actors.end();i++)
		{
			Actor *actor=*i;
			if (actor != player)
			{
				actor->update();
			}
		}
	}
}

void Engine::sendToBack(Actor *actor)
{
	actors.remove(actor);
	actors.insertBefore(actor,0);
}

void Engine::render()
{
	TCODConsole::root->clear();
	//draw the map
	map->render();
	//draw the actors
	for (Actor **iterator=actors.begin(); iterator != actors.end(); iterator++)
	{
		Actor *actor=*iterator;
		if (map->isInFov(actor->x,actor->y))
		{
			actor->render();
		}
	}
	topGui->renderLog();
	botGui->renderStatus();
}

Actor *Engine::getClosestMonster(int x, int y, float range) const
{
	Actor *closest=NULL;
	float bestDistance=1E6f;
	for (Actor **i=actors.begin(); i!=actors.end(); i++)
	{
		Actor *actor=*i;
		if (actor != player && actor->destructible && !actor->destructible->isDead())
		{
			float distance=actor->getDistance(x,y);
			if (distance < bestDistance && (distance <= range || range == 0.0f))
			{
				bestDistance=distance;
				closest=actor;
			}
		}
	}
	return closest;
}

void Engine::init()
{
	player = new Actor(40,25,'@',"player",TCODColor::white);
	player->destructible=new PlayerDestructible(30,2,"your cadaver");
	player->attacker=new Attacker(5);
	player->ai = new PlayerAi();
	player->container = new Container(26);
	actors.push(player);
	map = new Map(80,43);
	map -> init(true);
	topGui->message(TCODColor::red,"Welcome stranger\nPrepare to perish in the Tombs of the Ancient Kings.");
}

void Engine::save()
{
	if (player->destructible->isDead())
	{
		TCODSystem::deleteFile("game.sav");
	}
	else
	{
		TCODZip zip;
		//save the map first
		zip.putInt(map->width);
		zip.putInt(map->height);
		map->save(zip);
		//then the player
		player->save(zip);
		//then all the other actors
		zip.putInt(actors.size()-1);
		for (Actor **i=actors.begin(); i!=actors.end(); i++)
		{
			if (*i!=player)
			{
				(*i)->save(zip);
			}
		}
		// finally the message log
		topGui->save(zip);
		zip.saveToFile("game.sav");
	}
}

void Engine::load()
{
	if (TCODSystem::fileExists("game.sav"))
	{
		TCODZip zip;
		zip.loadFromFile("game.sav");
		//load the map
		int width=zip.getInt();
		int height=zip.getInt();
		map = new Map(width,height);
		map->load(zip);
		//then the player
		player=new Actor(0,0,0,NULL,TCODColor::white);
		player->load(zip);
		actors.push(player);
		//then all other actors
		int nbActors=zip.getInt();
		while (nbActors > 0)
		{
			Actor *actor = new Actor(0,0,0,NULL,TCODColor::white);
			actor->load(zip);
			actors.push(actor);
			sendToBack(actor);
			nbActors--;
		}
		//finally the message log
		topGui->load(zip);
	}
	else
	{
		engine.init();
	}
}
