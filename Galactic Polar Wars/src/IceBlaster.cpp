//THIS IS BASE. MODIFY AS NEEDED. REMINDER THAT CHECK TO SEE IF ITEMS ARE PROPERLY RESIZED BEFORE IMPLIMENTING INTO GAME!! -Vashj

#include "IceBlaster.h"
#include "TextureManager.h"


IceBlaster::IceBlaster()
{
	TextureManager::Instance()->load("../Assets/textures/IceBlaster.png", "iceBlaster");
	const auto size = TextureManager::Instance()->getTextureSize("iceblaster");
	setWidth(size.x);
	setHeight(size.y);
	getTransform()->position = glm::vec2(100.0f, 450.0f);
	getRigidBody()->velocity = glm::vec2(0, 0);
	getRigidBody()->isColliding = false;

	setType(FISH);

}
IceBlaster::~IceBlaster()
= default;
void IceBlaster::draw()
{

	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	TextureManager::Instance()->draw("iceblaster", getTransform()->position.x, getTransform()->position.y, 0, 255, true);

}
void IceBlaster::update()
{
}

void IceBlaster::clean()
{
}

void IceBlaster::m_checkBounds()
{
	m_checkBounds();
}

void IceBlaster::m_reset()
{
}