//THIS IS BASE. MODIFY AS NEEDED. REMINDER THAT CHECK TO SEE IF ITEMS ARE PROPERLY RESIZED BEFORE IMPLIMENTING INTO GAME!! -Vashj

#include "Keycard.h"
#include "TextureManager.h"


Keycard::Keycard()
{
	TextureManager::Instance()->load("../Assets/textures/Keycard.png", "keycard");
	const auto size = TextureManager::Instance()->getTextureSize("keycard");
	setWidth(size.x);
	setHeight(size.y);
	getTransform()->position = glm::vec2(430.0f, 120.0f);
	getRigidBody()->velocity = glm::vec2(0, 0);
	getRigidBody()->isColliding = false;

	setType(FISH);

}
Keycard::~Keycard()
= default;
void Keycard::draw()
{

	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	TextureManager::Instance()->draw("keycard", getTransform()->position.x, getTransform()->position.y, 0, 255, true);

}
void Keycard::update()
{
}

void Keycard::clean()
{
}

void Keycard::m_checkBounds()
{
	m_checkBounds();
}

void Keycard::m_reset()
{
}