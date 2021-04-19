#include "StoryBackground.h"

StoryBackground::StoryBackground()
{
	TextureManager::Instance()->load("../Assets/textures/StoryBackground.png", "StoryBackground");

	auto size = TextureManager::Instance()->getTextureSize("StoryBackground");
	setWidth(800);
	setHeight(600);
	setEnabled(true);
	setType(STORYBACKGROUND);
}

StoryBackground::~StoryBackground()
= default;

void StoryBackground::draw()
{
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	TextureManager::Instance()->draw("StoryBackground", 0, 0, 0, 255, false, SDL_FLIP_NONE);
}

void StoryBackground::update()
{

}

void StoryBackground::clean()
{
}

void StoryBackground::setDestination(const glm::vec2 destination)
{
	
}
