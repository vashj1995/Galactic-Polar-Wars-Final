#include "AlienBlaster.h"
#include "TextureManager.h"


AlienBlaster::AlienBlaster()
{
	TextureManager::Instance()->load("../Assets/textures/AlienBlaster.png", "alienblaster");
	const auto size = TextureManager::Instance()->getTextureSize("alienblaster");
	setWidth(size.x);
	setHeight(size.y);
	getTransform()->position = glm::vec2(100.0f, 450.0f);
	getRigidBody()->velocity = glm::vec2(0, 0);
	getRigidBody()->isColliding = false;

	setType(FISH);

}
AlienBlaster::~AlienBlaster()
= default;
void AlienBlaster::draw()
{

	TextureManager::Instance()->draw("alienblaster", getTransform()->draw_position.x, getTransform()->draw_position.y, 0, 255, true);

}
void AlienBlaster::update()
{
}

void AlienBlaster::clean()
{
}

void AlienBlaster::m_checkBounds()
{
	m_checkBounds();
}

void AlienBlaster::m_reset()
{
}