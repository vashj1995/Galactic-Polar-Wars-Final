//THIS IS BASE. MODIFY AS NEEDED. REMINDER THAT CHECK TO SEE IF ITEMS ARE PROPERLY RESIZED BEFORE IMPLIMENTING INTO GAME!! -Vashj


#include "Swordfish.h"
#include "TextureManager.h"


Swordfish::Swordfish()
{
	TextureManager::Instance()->load("../Assets/textures/Swordfish.png", "swordfish");
	const auto size = TextureManager::Instance()->getTextureSize("swordfish");
	setWidth(size.x);
	setHeight(size.y);
	getTransform()->position = glm::vec2(100.0f, 450.0f);
	getRigidBody()->velocity = glm::vec2(0, 0);
	getRigidBody()->isColliding = false;

	setType(FISH);

}
Swordfish::~Swordfish()
= default;
void Swordfish::draw()
{

	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	TextureManager::Instance()->draw("swordfish", getTransform()->position.x, getTransform()->position.y, 0, 255, true);

}
void Swordfish::update()
{
}

void Swordfish::clean()
{
}

void Swordfish::m_checkBounds()
{
	m_checkBounds();
}

void Swordfish::m_reset()
{
}