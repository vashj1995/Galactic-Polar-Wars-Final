#include "TileMap.h"

#include <utility>

TileMap::TileMap(std::string name, SDL_Texture* texture)
	:m_name(std::move(name)), m_texture(texture)
{}

TileMap::TileMap(std::string name)
	: m_name(std::move(name)), m_texture(nullptr)
{
}

TileMap::~TileMap()
= default;

void TileMap::setTexture(SDL_Texture * texture)
{
	m_texture = texture;
}

Tile TileMap::getTile(const std::string& tile_name)
{
	return m_tiles[tile_name];
}

std::unordered_map<std::string, Tile> TileMap::getTiles() const
{
	return m_tiles;
}

SDL_Texture* TileMap::getTexture(const std::string key) const
{
	return m_texture;
}

void TileMap::addTile(const Tile& tile)
{
	m_tiles[tile.key] = tile;
}

