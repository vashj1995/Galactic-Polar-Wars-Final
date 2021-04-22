#include "Level.h"

#include <iostream>
#include "Floor.h"
#include "TextureManager.h"

Level::Level(int cols, int rows, LevelType level_type):m_cols(cols), m_rows(rows), m_levelType(level_type)
{
	setTileMap(TextureManager::Instance()->getTileMap("TileMap"));
	// LevelData is what to draw where. 
	m_pTiles = m_pTileMap->getTiles();

	if(level_type == FREEZER)
	{
		readLevelData("../Assets/sprites/FreezerlvlLayoutFinal.txt");
	}
	else if(level_type == ENGINE)
	{
		readLevelData("../Assets/sprites/EngineRoomLayout.txt"); 
	}
	else if(level_type == BOSS)
	{
		readLevelData("../Assets/sprites/BossLevelLayout.txt"); 
	}

}

Level::~Level()
= default;

TileMap* Level::getTileMap() const
{
	return m_pTileMap;
}

Tile& Level::getTile(const std::string & name)
{
	return m_pTiles[name];
}

void Level::draw()
{
}

void Level::update()
{
}

void Level::clean()
{
}

// Pass in the vector of DisplayObjects where the Platforms will be created.
void Level::addTiles(std::vector<DisplayObject*>& platform_vector, std::vector<DisplayObject*>& decoration_vector)
{
	int i = 0;
	for (int row = 0; row < m_rows; row++)
	{
		for (int col = 0; col < m_cols; col++)
		{

			if(m_levelData[i] != "e")
			{
				if(m_pTiles[std::string(m_levelData[i])].t == 0)
					platform_vector.push_back(new Platform(glm::vec2(col * 40, row * 40), m_levelData[i], TILE_PLATFORM));
				
				if(m_pTiles[std::string(m_levelData[i])].t == 1)
					platform_vector.push_back(new Platform(glm::vec2(col * 40, row * 40), m_levelData[i], TILE_HAZARD));
				
				if(m_pTiles[std::string(m_levelData[i])].t == 2)
					decoration_vector.push_back(new Platform(glm::vec2(col * 40, row * 40), m_levelData[i], TILE_DECORATION));
				
				if(m_pTiles[std::string(m_levelData[i])].t == 3)
					platform_vector.push_back(new Platform(glm::vec2(col * 40, row * 40), m_levelData[i], TILE_DOOR));
			}
			i++;
		}
	}
	platform_vector.shrink_to_fit();
	decoration_vector.shrink_to_fit();
}

void Level::setTileMap(TileMap* tile_map)
{
	m_pTileMap = tile_map;
}

void Level::setTile(const Tile &tile)
{
	if (!m_tileExists(tile.key))
	{
		m_pTiles[tile.key] = tile;
	}
}

int Level::getCols()
{
	return m_cols;
}

int Level::getRows()
{
	return m_rows;
}

// Reads the data into a string vector in order.
void Level::readLevelData(const std::string& level_data_file_name)
{
	std::ifstream inFile(level_data_file_name);
	if (inFile.is_open())
	{
		std::string key;
		while (!inFile.eof())
		{
			inFile >> key;
			m_levelData.push_back(key);
		}
	}
	if (inFile.fail())
		std::cout << "Tile Level data read failed!" << std::endl;
	else
		std::cout << "Tile Level data read successful!" << std::endl;
	inFile.close();
}


bool Level::m_tileExists(const std::string & id)
{
	return m_pTiles.find(id) != m_pTiles.end();
}
