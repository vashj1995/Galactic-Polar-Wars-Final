#include "PlatformLong.h"
#include "TextureManager.h"
#include "SoundManager.h"


PlatformLong::PlatformLong()
{
	TextureManager::Instance()->load("../Assets/textures/GPW_Freezer_ShelfLong.png", "platformlong");

	const auto size = TextureManager::Instance()->getTextureSize("platformlong");
	setWidth(size.x);
	setHeight(size.y);
	getTransform()->position = glm::vec2(100.0f, 400.0f);
	getRigidBody()->velocity = glm::vec2(0, 0);
	getRigidBody()->isColliding = false;

	setType(PLATFORM); //changed from TARGET to PLATFORM - soph

	SoundManager::Instance().load("../Assets/audio/yay.ogg", "yay", SOUND_SFX); // added sound fx for collision
}

void PlatformLong::m_checkBounds()
{
}

PlatformLong::~PlatformLong()
= default;

void PlatformLong::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the platform
	TextureManager::Instance()->draw("platformlong",
		getTransform()->position.x, getTransform()->position.y, 0, 255, true);

	//TextureManager::Instance()->draw("platformlong", x, y, 0, 255, true); changed x and y to getTransform() - soph
}

void PlatformLong::update()
{
	m_checkBounds();
}

void PlatformLong::clean()
{
}

void PlatformLong::m_reset()
{
}
