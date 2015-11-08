// #include "main.hpp"
#include "libtcod.hpp"
#include "TCODMapGenerator.hpp"
#include <iostream>

using namespace std;

static const int ROOM_MAX_SIZE = 12;
static const int ROOM_MIN_SIZE = 6;
static const int MAX_ROOM_MONSTERS = 3;
static const int MAX_ROOM_ITEMS = 2;

class Room
// rooms should connect to other rooms, corridors can cross each other
{
public:
    Room(int x1, int y1, int x2, int y2, int number) : x1(x1), y1(y1), x2(x2), y2(y2), number(number) {}

    int x1, y1, x2, y2;
    int number;
    int numExits;
};

class BspListener : public ITCODBspCallback
{
private :
    Map &map; // a map to dig
    int roomNum; // room number
    int lastx,lasty; // center of the last room
    TCODRandom* rng;
    TCODList<Room*> roomList;

public :
    BspListener(Map &map, TCODList<Room*> roomList) : map(map), roomNum(0) 
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
                roomList.push(new Room(x, y, x+w-1, y+h-1, roomNum));
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
    TCODList<Room*> roomList;

    BspListener listener(*map, roomList);
    bsp.traverseInvertedLevelOrder(&listener, (void*)true);

    cout << roomList.size() << " woo" << endl;
    
    return map;
}

Map* TCODMapGenerator::makeEmptyMap(Map* map)
{
        map->map = new TCODMap(map->width, map->height);
        map->createRoom(true, 10, 10, 40, 40, true);

        return map;
}

// void TCODMapGenerator::createRoom(int x1, int y1, int x2, int y2)
// {
   
// }
