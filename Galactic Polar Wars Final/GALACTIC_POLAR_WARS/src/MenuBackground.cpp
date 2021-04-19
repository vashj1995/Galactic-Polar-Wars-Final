#include "MenuBackground.h"

MenuBackground::MenuBackground();
{
	TextureManager::Instance()->load("../Assets/Textures/MenuBackground.png", "MenuBackground");

	auto size = TextureManager::Instance()->getTextureSize("MenuBackground");
	setWidth(800);
	setHeight(600);
	setEnabled(true);
	setType(BACKGROUND3);
}

MenuBackground::~MenuBackground()
= default;

void MenuBackground::draw()
{
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	TextureManager::Instance()->draw("MenuBackground", 400, 300, 0, 255, true, SDL_FLIP_NONE);
	//getTransform()->position.x, getTransform()->position.y,255, true);
}

void MenuBackground::update()
{

}

void MenuBackground::clean()
{

}

void MenuBackground::setDestination(const glm::vec2 destination)
{
	//m_destination=destination;
}