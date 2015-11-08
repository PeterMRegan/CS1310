#include "main.hpp"

static const int ROOM_MAX_SIZE = 12;
static const int ROOM_MIN_SIZE = 6;
static const int MAX_ROOM_MONSTERS = 3;
static const int MAX_ROOM_ITEMS = 2;

Map::Map(int width, int height) : width(width),height(height)
{
	seed=TCODRandom::getInstance()->getInt(0,0x7FFFFFFF);
}

Map::~Map()
{
	delete [] tiles;
	delete map;
}

bool Map::isWall(int x, int y) const
{
	return !map->isWalkable(x,y);
}

bool Map::canWalk(int x, int y) const
{
	if (isWall(x,y))
	{
		//this is a wall
		return false;
	}
	for (Actor **i=engine.actors.begin();i!=engine.actors.end();i++)
	{
		Actor *actor=*i;
		if (actor->blocks && actor->x == x && actor->y == y)
		{
			//there is a blocking actor here.
			return false;
		}
	}
	return true;
}

bool Map::isExplored(int x, int y) const
{
	return tiles[x+y*width].explored;
}

bool Map::isInFov(int x, int y) const
{
	if (map->isInFov(x,y))
	{
		tiles[x+y*width].explored=true;
		return true;
	}
	return false;
}

void Map::addMonster(int x, int y)
{
	TCODRandom *rng=TCODRandom::getInstance();
	if (rng->getInt(0,100) < 80)
	{
		//create an orc
		Actor *orc = new Actor(x,y,'o',"orc",TCODColor::desaturatedGreen);
		orc->destructible = new MonsterDestructible(10,0,"dead orc");
		orc->attacker = new Attacker(3);
		orc->ai = new MonsterAi();
		engine.actors.push(orc);
		engine.monsters.push(orc);
	}
	else
	{
		//create a troll
		Actor *troll = new Actor(x,y,'T',"troll",TCODColor::darkerGreen);
		troll->destructible = new MonsterDestructible(16,1,"troll carcass");
		troll->attacker = new Attacker(4);
		troll->ai = new MonsterAi();
		engine.actors.push(troll);
		engine.monsters.push(troll);
	}
}

void Map::addItem(int x, int y)
{
	TCODRandom *rng=TCODRandom::getInstance();
	int dice = rng->getInt(0,100);
	if (dice < 50)
	{
		//create a potion of cure minor wounds
		Actor *cureLightPotion=new Actor(x,y,'!',"potion of cure minor wounds",TCODColor::violet);
		cureLightPotion->blocks=false;
		cureLightPotion->pickable=new Healer(4);
		engine.actors.push(cureLightPotion);
		engine.sendToBack(cureLightPotion);
	}
	else if (dice < 70)
	{
		//create a potion of cure serious wounds
		Actor *cureSeriousPotion=new Actor(x,y,'!',"potion of cure serious wounds",TCODColor::blue);
		cureSeriousPotion->blocks=false;
		cureSeriousPotion->pickable=new Healer(12);
		engine.actors.push(cureSeriousPotion);
		engine.sendToBack(cureSeriousPotion);
	}
	else if (dice <= 100)
	{
		//create a scroll of lightning bolt
		Actor *scrollOfLightningBolt=new Actor(x,y,'?',"scroll of lightning bolt", TCODColor::lightYellow);
		scrollOfLightningBolt->blocks=false;
		scrollOfLightningBolt->pickable=new LightningBolt(5,20);
		engine.actors.push(scrollOfLightningBolt);
		engine.sendToBack(scrollOfLightningBolt);
	}
}

void Map::computeFov()
{
	map->computeFov(engine.player->x,engine.player->y,engine.fovRadius);
}

void Map::dig(int x1, int y1, int x2, int y2)
{
	if (x2 < x1)
	{
		int tmp=x2;
		x2=x1;
		x1=tmp;
	}
	if (y2 < y1)
	{
		int tmp=y2;
		y2=y1;
		y1=tmp;
	}
	for (int tilex=x1; tilex <= x2; tilex++)
	{
		for (int tiley=y1; tiley <= y2; tiley++)
		{
			map->setProperties(tilex,tiley,true,true);
		}
	}
}

void Map::createRoom(bool first, int x1, int y1, int x2, int y2, bool withActors)
{
	dig (x1,y1,x2,y2);
	if (!withActors)
	{
		return;
	}
	if (first)
	{
		//put the player in the first room
		engine.player->x=(x1+x2)/2;
		engine.player->y=(y1+y2)/2;
	}
	else
	{
		TCODRandom *rng=TCODRandom::getInstance();
		//add monsters
		int nbMonsters=rng->getInt(0,MAX_ROOM_MONSTERS);
		while (nbMonsters > 0)
		{
			int x=rng->getInt(x1,x2);
			int y=rng->getInt(y1,y2);
			if (canWalk(x,y))
			{
				addMonster(x,y);
			}
			nbMonsters--;
		}
		//add items
		int nbItems=rng->getInt(0,MAX_ROOM_ITEMS);
		while (nbItems > 0)
		{
			int x=rng->getInt(x1,x2);
			int y=rng->getInt(y1,y2);
			if (canWalk(x,y))
			{
				addItem(x,y);
			}
			nbItems--;
		}
	}
	//set stairs position
	engine.stairs->x=(x1+x2)/2;
	engine.stairs->y=(y1+y2)/2;
}

void Map::render() const
{
	static const TCODColor darkWall(0,0,100);
	static const TCODColor darkGround(50,50,150);
	static const TCODColor lightWall(130,110,50);
	static const TCODColor lightGround(200,180,50);
	for (int x=0; x < width; x++)
	{
		for (int y=0; y < height; y++)
		{
			if (isInFov(x,y))
			{
				TCODConsole::root->setCharBackground(x,y+MAP_OFFSET,isWall(x,y)?lightWall:lightGround);
			}
			else if ( isExplored(x,y))
			{
				TCODConsole::root->setCharBackground(x,y+MAP_OFFSET,isWall(x,y)?darkWall:darkGround);
			}
		}
	}
}

void Map::init(bool withActors)
{
        rng = new TCODRandom(seed, TCOD_RNG_CMWC);
	tiles=new Tile[width*height];
	map=new TCODMap(width,height);
}

void Map::save(TCODZip &zip)
{
	zip.putInt(seed);
	for (int i=0; i<width*height; i++)
	{
		zip.putInt(tiles[i].explored);
	}
}

void Map::load(TCODZip &zip)
{
	seed = zip.getInt();
	init(false);
	for (int i=0;i<width*height;i++)
	{
		tiles[i].explored=zip.getInt();
	}
}
