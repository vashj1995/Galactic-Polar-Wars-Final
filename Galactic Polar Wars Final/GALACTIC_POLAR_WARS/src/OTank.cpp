//THIS IS BASE. MODIFY AS NEEDED. REMINDER THAT CHECK TO SEE IF ITEMS ARE PROPERLY RESIZED BEFORE IMPLIMENTING INTO GAME!! -Vashj


#include "OTank.h"
#include "TextureManager.h"


OTank::OTank()
{
	TextureManager::Instance()->load("../Assets/textures/OxygenTank.png", "OxygenTank");
	const auto size = TextureManager::Instance()->getTextureSize("OxygenTank");
	setWidth(size.x);
	setHeight(size.y);
	getTransform()->position = glm::vec2(430.0f, 120.0f);
	getRigidBody()->velocity = glm::vec2(0, 0);
	getRigidBody()->isColliding = false;

	setType(FISH);

}
OTank::~OTank()
= default;
void OTank::draw()
{

	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	TextureManager::Instance()->draw("OkygenTank", getTransform()->position.x, getTransform()->position.y, 0, 255, true);

}
void OTank::update()
{
}

void OTank::clean()
{
}

void OTank::m_checkBounds()
{
	m_checkBounds();
}

void OTank::m_reset()
{
}