#include "main.hpp"
#include <iostream>

using namespace std;

static const int ROOM_MAX_SIZE = 12;
static const int ROOM_MIN_SIZE = 6;
static const int MAX_ROOM_MONSTERS = 3;
static const int MAX_ROOM_ITEMS = 2;

class BspListener : public ITCODBspCallback
{
private :
    Map &map; // a map to dig
    int roomNum; // room number
    int lastx,lasty; // center of the last room
    TCODRandom* rng;

public :
    BspListener(Map &map) : map(map), roomNum(0) 
    {
        rng = new TCODRandom(TCODRandom::getInstance()->getInt(0,0x7FFFFFFF), TCOD_RNG_CMWC);
    }

    bool visitNode(TCODBsp *node, void *userData)
    {
        if (node->isLeaf())
            {
                int x,y,w,h;
                bool withActors=(bool)userData;
                //dig a room
                w=rng->getInt(ROOM_MIN_SIZE, node->w-2);
                h=rng->getInt(ROOM_MIN_SIZE, node->h-2);
                x=rng->getInt(node->x+1, node->x+node->w-w-1);
                y=rng->getInt(node->y+1, node->y+node->h-h-1);
                map.createRoom(roomNum == 0, x, y, x+w-1, y+h-1, withActors);
                if (roomNum != 0)
                    {
                        //dig a cooridor from last room
                        map.dig(lastx,lasty,x+w/2,lasty);
                        map.dig(x+w/2,lasty,x+w/2,y+h/2);
                    }
                lastx=x+w/2;
                lasty=y+h/2;
                roomNum++;
            }
        return true;
    }
};

TCODMapGenerator::TCODMapGenerator() 
{
}

Map* TCODMapGenerator::makeDefaultMap(Map* map)
{
    TCODRandom* rng = new TCODRandom(TCODRandom::getInstance()->getInt(0,0x7FFFFFFF), TCOD_RNG_CMWC);
    TCODBsp bsp(0,0,map->width,map->height);
    bsp.splitRecursive(rng, 8, ROOM_MAX_SIZE, ROOM_MAX_SIZE, 1.5f, 1.5f);

    BspListener listener(*map);
    bsp.traverseInvertedLevelOrder(&listener, (void*)true);
    
    return map;
}

Map* TCODMapGenerator::makeEmptyMap(Map* map)
{
        map->createRoom(true, 10, 10, 40, 40, true);

        return map;
}
