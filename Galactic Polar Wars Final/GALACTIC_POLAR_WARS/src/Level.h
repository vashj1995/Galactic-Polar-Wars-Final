#pragma once
#ifndef __LEVEL__
#define __LEVEL__
#include <vector>
#include <fstream>
#include <map>
#include <SDL.h>


#include "Platform.h"
#include "TileMap.h"

// Level takes the TileMap data and creates Platforms at the designated position in the vector.

class Level : public DisplayObject
{
public:
	Level(int rows, int cols, LevelType level_type);
	~Level();


	// getters
	TileMap* getTileMap() const;
	Tile& getTile(const std::string& name);

	void addTiles(std::vector<DisplayObject*>& platform_vector, std::vector<DisplayObject*>& decoration_vector);

	void draw() override;
	void update() override;
	void clean() override;
	
	// setters
	void setTileMap(TileMap* tile_map);
	void setTile(const Tile& tile);

	int getCols();
	int getRows();

	void readLevelData(const std::string& level_data_file_name);

private:
	// private utility functions
	bool m_tileExists(const std::string& id);

private:
	TileMap *m_pTileMap;

	std::unordered_map<std::string, Tile> m_pTiles;
	std::map<char, Tile*> m_tileData;

	std::vector<std::string> m_levelData;
	std::vector<int> m_levelTileData;
	LevelType m_levelType;
	int m_cols; // = 86, m_rows = 19;
	int m_rows;
	//int m_cols = 41, m_rows = 19;
};

#endif /* defined (__LEVEL__) */