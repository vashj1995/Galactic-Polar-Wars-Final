#include "EngineBackground.h"

EngineBackground::EngineBackground()
{
	TextureManager::Instance()->load("../Assets/textures/Engine_Cockpit_Background.png", "EngineBackground");

	auto size = TextureManager::Instance()->getTextureSize("EngineBackground");
	setWidth(1280);
	setHeight(800);
	getTransform()->position = glm::vec2(0, 0);
	setEnabled(true);
	setType(BACKGROUND3);
}

EngineBackground::~EngineBackground()
= default;

void EngineBackground::draw()
{

	TextureManager::Instance()->draw("EngineBackground", 0, 0, 0, 255, false, SDL_FLIP_NONE);

}

void EngineBackground::update()
{

}

void EngineBackground::clean()
{
}

void EngineBackground::setDestination(const glm::vec2 destination)
{
	//m_destination = destination;
}
