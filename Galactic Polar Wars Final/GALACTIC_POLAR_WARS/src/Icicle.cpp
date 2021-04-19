//THIS IS BASE. MODIFY AS NEEDED. REMINDER THAT CHECK TO SEE IF ITEMS ARE PROPERLY RESIZED BEFORE IMPLIMENTING INTO GAME!! -Vashj

#include "Icicle.h"
#include "TextureManager.h"


Icicle::Icicle()
{
	TextureManager::Instance()->load("../Assets/textures/Icicle.png", "icicle");
	const auto size = TextureManager::Instance()->getTextureSize("icicle");
	setWidth(size.x);
	setHeight(size.y);
	getTransform()->position = glm::vec2(100.0f, 450.0f);
	getRigidBody()->velocity = glm::vec2(0, 0);
	getRigidBody()->isColliding = false;

	setType(FISH);

}
Icicle::~Icicle()
= default;
void Icicle::draw()
{

	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	TextureManager::Instance()->draw("icicle", getTransform()->position.x, getTransform()->position.y, 0, 255, true);

}
void Icicle::update()
{
}

void Icicle::clean()
{
}

void Icicle::m_checkBounds()
{
	m_checkBounds();
}

void Icicle::m_reset()
{
}