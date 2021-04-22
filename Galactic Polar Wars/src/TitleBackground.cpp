#include "TitleBackground.h"

TitleBackground::TitleBackground()
{
	TextureManager::Instance()->load("../Assets/textures/TitleBackground.png", "TitleBackground");

	auto size = TextureManager::Instance()->getTextureSize("TitleBackground");
	setWidth(800);
	setHeight(600);
	setEnabled(true);
	setType(BACKGROUND1);
}

TitleBackground::~TitleBackground()
= default;

void TitleBackground::draw()
{
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	TextureManager::Instance()->draw("TitleBackground", 0, 0, 0, 255, false, SDL_FLIP_NONE);
}

void TitleBackground::update()
{

}

void TitleBackground::clean()
{
}

void TitleBackground::setDestination(const glm::vec2 destination)
{
}
