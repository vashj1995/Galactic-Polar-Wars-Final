#pragma once
#ifndef __PLATFORM__
#define __PLATFORM__

#include "DisplayObject.h"
#include "PlatformType.h"
#include "TileMap.h"

class Platform final : public DisplayObject
{
	friend class TileMap;
public:
	Platform();
	Platform(glm::vec2 position, std::string key, GameObjectType type);
	~Platform();

	// Inherited via GameObject
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	std::string getTileKey() const;
	std::string m_tileKey;
private:
	TileMap* m_pTileMap;
	void m_checkBounds();
	void m_reset();
};


#endif /* defined (__PLATFORM__) */
