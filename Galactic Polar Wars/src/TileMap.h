#pragma once
#ifndef __TILE_MAP__
#define __TILE_MAP__
#include <vector>
#include <unordered_map>
#include <SDL.h>

#include "Tile.h"

// Set up very similarly to SpriteSheet class.
class TileMap
{
public:
	TileMap(std::string name, SDL_Texture* texture);
	TileMap(std::string name);
	~TileMap();

	// getters
	Tile getTile(const std::string& tile_name);
	std::unordered_map<std::string, Tile> getTiles() const;
	SDL_Texture* getTexture(const std::string key) const;

	// setters
	void addTile(const Tile& tile);
	void addType(int i);
	void setTexture(SDL_Texture* texture);

private:
	std::string m_name;
	std::unordered_map<std::string, Tile> m_tiles;

	SDL_Texture* m_texture;
};

#endif /* defined (__TILE_MAP__) */
