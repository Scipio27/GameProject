#include "Map.h"

Map::Map(){
}

void Map::addRoomToMap(Room* r)
{
	map.push_back(r);
}