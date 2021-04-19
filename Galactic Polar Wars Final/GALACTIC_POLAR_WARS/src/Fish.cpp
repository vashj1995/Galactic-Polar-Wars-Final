//THIS IS BASE. MODIFY AS NEEDED. REMINDER THAT CHECK TO SEE IF ITEMS ARE PROPERLY RESIZED BEFORE IMPLIMENTING INTO GAME!! -Vashj

#include "Fish.h"
#include "TextureManager.h"


Fish::Fish()
{
	TextureManager::Instance()->load("../Assets/textures/fish.png", "fish");
	const auto size = TextureManager::Instance()->getTextureSize("fish");
	setWidth(size.x);
	setHeight(size.y);
	getTransform()->position = glm::vec2(430.0f, 120.0f);
	getRigidBody()->velocity = glm::vec2(0, 0);
	getRigidBody()->isColliding = false;

	setType(FISH);

}
Fish::~Fish()
{
	
}
void Fish::draw()
{

	TextureManager::Instance()->draw("fish", getTransform()->draw_position.x, getTransform()->draw_position.y, 0, 255, true);

}
void Fish::update()
{
}

void Fish::clean()
{
}

void Fish::m_checkBounds()
{
	m_checkBounds();
}

void Fish::m_reset()
{
}