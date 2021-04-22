//THIS IS BASE. MODIFY AS NEEDED. REMINDER THAT CHECK TO SEE IF ITEMS ARE PROPERLY RESIZED BEFORE IMPLIMENTING INTO GAME!! -Vashj


#include "Ammo.h"
#include "TextureManager.h"


Ammo::Ammo()
{
	TextureManager::Instance()->load("../Assets/textures/Ammunition.png", "ammo");
	const auto size = TextureManager::Instance()->getTextureSize("ammo");
	setWidth(size.x);
	setHeight(size.y);
	getTransform()->position = glm::vec2(430.0f, 120.0f);
	getRigidBody()->velocity = glm::vec2(0, 0);
	getRigidBody()->isColliding = false;

	setType(FISH);

}
Ammo::~Ammo()
= default;
void Ammo::draw()
{

	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	TextureManager::Instance()->draw("ammo", getTransform()->position.x, getTransform()->position.y, 0, 255, true);

}
void Ammo::update()
{
}

void Ammo::clean()
{
}

void Ammo::m_checkBounds()
{
	m_checkBounds();
}

void Ammo::m_reset()
{
}