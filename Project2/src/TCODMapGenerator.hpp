// #include "MapGenerator.cpp"
#ifndef TCODMAPGEN_HPP
#define TCODMAPGEN_HPP
#include "Map.hpp"
class TCODMapGenerator
{
public :
        TCODMapGenerator();
  
        static Map* makeDefaultMap(Map *map);
        static Map* makeEmptyMap(Map* map);
protected:
        friend class BspListener;
};
#endif
