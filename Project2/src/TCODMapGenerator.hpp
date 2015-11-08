// #include "MapGenerator.cpp"

class TCODMapGenerator
{
public :
        TCODMapGenerator();
  
        static Map* makeDefaultMap(Map *map);
        static Map* makeEmptyMap(Map* map);
protected:
        friend class BspListener;
};
