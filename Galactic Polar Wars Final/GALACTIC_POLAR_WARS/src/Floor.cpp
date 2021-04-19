#include "Floor.h"
#include "TextureManager.h"



Floor::Floor()
{
	TextureManager::Instance()->load("../Assets/textures/Floor.png", "floor");

	const auto size = TextureManager::Instance()->getTextureSize("floor");
	setWidth(size.x);
	setHeight(size.y);
	getTransform()->position = glm::vec2(0.0f, 800.0f);
	getRigidBody()->isColliding = false;

	setType(FLOOR); 

}

// Parameterized Platform constructor. Takes in the position & type of platform.
// Type so we don't need to create many classes for essentially the same thing.
Floor::Floor(glm::vec2 position, FloorType type)
{
	// Set the FloorType to use in draw() method.
	setFloorType(type);

	// Based on the type, load a specific asset:
	switch (type)
	{
	case FF1:
		TextureManager::Instance()->load("../Assets/textures/FreezerFloor_1.png", "frzr_floor_1");
		break;
	case FF2:
		TextureManager::Instance()->load("../Assets/textures/FreezerFloor_2.png", "frzr_floor_2");
		break;
	case AF:
		//TextureManager::Instance()->load("../Assets/textures/AquaFloor.png", "aqua_floor");
		break;
	case EF:
		//TextureManager::Instance()->load("../Assets/textures/EngineFloor.png", "engn_floor");
		break;
	case SPF:
		//TextureManager::Instance()->load("../Assets/textures/SpaceFloor.png", "spce_floor");
		break;
	//TODO: Add proper files to folders & uncomment each case above.
	}

	// Floor tiles will always be 40 x 40, so hard-coding the values.
	setWidth(40);
	setHeight(40);

	// Set position to the glm::vec2(x,y) passed in.
	getTransform()->position = position;
	
	getRigidBody()->isColliding = false;

	setType(FLOOR); 

}

Floor::~Floor()
= default;

void Floor::draw()
{
	// alias for x and y
	const auto x = getTransform()->draw_position.x;
	const auto y = getTransform()->draw_position.y;

	// Draw the floor based on its type.
	switch (m_floorType)
	{
	case FF1:
		TextureManager::Instance()->draw("frzr_floor_1", x, y, 0, 255, true);
		break;
	case FF2:
		TextureManager::Instance()->draw("frzr_floor_2", x, y, 0, 255, true);
		break;
	//TODO: Add more cases here as needed.
	// Make sure to add to the enum 'FloorType' as well.
	}

}

void Floor::update()
{
	m_checkBounds();
}

void Floor::clean()
{
}

void Floor::setFloorType(FloorType type)
{
	this->m_floorType = type;
}

FloorType Floor::getFloorType() const
{
	return m_floorType;
}

void Floor::m_checkBounds()
{
}

void Floor::m_reset()
{
}
