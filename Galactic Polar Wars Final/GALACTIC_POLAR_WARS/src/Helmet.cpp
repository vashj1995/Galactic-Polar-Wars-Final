//THIS IS BASE. MODIFY AS NEEDED. REMINDER THAT CHECK TO SEE IF ITEMS ARE PROPERLY RESIZED BEFORE IMPLIMENTING INTO GAME!! -Vashj


#include "Helmet.h"
#include "TextureManager.h"


Helmet::Helmet()
{
	TextureManager::Instance()->load("../Assets/textures/Helmet.png", "helmet");
	const auto size = TextureManager::Instance()->getTextureSize("helmet");
	setWidth(size.x);
	setHeight(size.y);
	getTransform()->position = glm::vec2(430.0f, 120.0f);
	getRigidBody()->velocity = glm::vec2(0, 0);
	getRigidBody()->isColliding = false;

	setType(FISH);

}
Helmet::~Helmet()
= default;
void Helmet::draw()
{

	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	TextureManager::Instance()->draw("helmet", getTransform()->position.x, getTransform()->position.y, 0, 255, true);

}
void Helmet::update()
{
}

void Helmet::clean()
{
}

void Helmet::m_checkBounds()
{
	m_checkBounds();
}

void Helmet::m_reset()
{
}