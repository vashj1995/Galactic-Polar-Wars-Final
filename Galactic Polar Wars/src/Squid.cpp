//THIS IS BASE. MODIFY AS NEEDED. REMINDER THAT CHECK TO SEE IF ITEMS ARE PROPERLY RESIZED BEFORE IMPLIMENTING INTO GAME!! -Vashj


#include "Squid.h"
#include "TextureManager.h"


Squid::Squid()
{
	TextureManager::Instance()->load("../Assets/textures/Squid.png", "squid");
	const auto size = TextureManager::Instance()->getTextureSize("squid");
	setWidth(size.x);
	setHeight(size.y);
	getTransform()->position = glm::vec2(100.0f, 450.0f);
	getRigidBody()->velocity = glm::vec2(0, 0);
	getRigidBody()->isColliding = false;

	setType(FISH);

}
Squid::~Squid()
= default;
void Squid::draw()
{

	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	TextureManager::Instance()->draw("squid", getTransform()->position.x, getTransform()->position.y, 0, 255, true);

}
void Squid::update()
{
}

void Squid::clean()
{
}

void Squid::m_checkBounds()
{
	m_checkBounds();
}

void Squid::m_reset()
{
}