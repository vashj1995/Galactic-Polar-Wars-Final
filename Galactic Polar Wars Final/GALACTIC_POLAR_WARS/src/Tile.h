#pragma once
#ifndef __TILE__
#define __TILE__
#include <string>


//enum TileType { PLAT, HAZARD, DECO }; // PLAT = 0, HAZARD = 1, DECO = 2

struct Tile //: public DisplayObject
{
	//Tile();
	//~Tile();

	//TileType tileType = (TileType)type;
	std::string key;
	int x;
	int y;
	int w;
	int h;
	int t;
};

#endif /* defined (__TILE__) */