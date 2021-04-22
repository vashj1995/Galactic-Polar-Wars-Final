#include "FreezerBackground.h"

FreezerBackground::FreezerBackground()
{
	TextureManager::Instance()->load("../Assets/textures/FreezerBackground.png", "FreezeBackground");

	auto size = TextureManager::Instance()->getTextureSize("FreezeBackground");
	setWidth(1280);
	setHeight(800);
	getTransform()->position = glm::vec2(0, 0);
	setEnabled(true);
	setType(BACKGROUND2);
}

FreezerBackground::~FreezerBackground()
= default;

void FreezerBackground::draw()
{

	TextureManager::Instance()->draw("FreezeBackground", getTransform()->position.x, getTransform()->position.y, 0, 255, false, SDL_FLIP_NONE);

}

void FreezerBackground::update()
{

}

void FreezerBackground::clean()
{
}

void FreezerBackground::setDestination(const glm::vec2 destination)
{
	//m_destination = destination;
}
