#include "Platform.h"
#include "TextureManager.h"
#include "SoundManager.h"

// Default Constructor.
Platform::Platform()
{
	m_pTileMap = TextureManager::Instance()->getTileMap("TileMap");
	
	TextureManager::Instance()->load("../Assets/textures/GPW_Freezer_ShelfLong.png", "platform");

	const auto size = TextureManager::Instance()->getTextureSize("platform");
	setWidth(40);
	setHeight(40);
	getTransform()->position = glm::vec2(100.0f, 400.0f); 
	getRigidBody()->velocity = glm::vec2(0, 0);
	getRigidBody()->isColliding = false;

	setType(TILE_PLATFORM);

}

Platform::Platform(glm::vec2 position, std::string key, GameObjectType type)
{
	// Set the TileMap & key. TileKey holds the string that references which part of the TileMap to draw.
	m_pTileMap = TextureManager::Instance()->getTileMap("TileMap");
	m_tileKey = key;

	TextureManager::Instance()->load("../Assets/textures/FreezerFloor.png", "e");

	if (m_tileKey == "e")
	{
		setEnabled(false);
		setType(EMPTY);
	}
	else
		setType(type);


	// All tiles are 40, so setting to 40.
	setWidth(40);
	setHeight(40);
	getTransform()->position = position; 
	getRigidBody()->velocity = glm::vec2(0, 0);
	getRigidBody()->isColliding = false;


}

Platform::~Platform()
{
	
}


void Platform::draw()
{
	// alias for x and y
	const auto x = getTransform()->draw_position.x;
	const auto y = getTransform()->draw_position.y;

	if(m_tileKey != "e")
		TextureManager::Instance()->drawTile("TileMap", m_tileKey, x, y, 0, 255, true);
}

void Platform::update()
{
}

void Platform::clean()
{
}

std::string Platform::getTileKey() const
{
	return m_tileKey;
}

void Platform::m_checkBounds()
{
}

void Platform::m_reset()
{
}

