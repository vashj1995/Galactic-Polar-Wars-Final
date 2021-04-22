#include "BossDecoration.h"

BossDecoration::BossDecoration(BossDecoType type, glm::vec2 pos)
{
	m_type = type;
	getTransform()->position = pos;
	
	switch (m_type)
	{
	case BD_CONSOLE:
		TextureManager::Instance()->load("../Assets/textures/Cockpit_Console.png", "BossDecoConsole");
		setWidth(216);
		setHeight(149);
		break;
	case BD_WINDOW:
		TextureManager::Instance()->load("../Assets/textures/Cockpit_Window.png", "BossDecoWindow");
		setWidth(828);
		setHeight(429);
		break;
	}
}

BossDecoration::~BossDecoration()
{
}

void BossDecoration::draw()
{
	const auto x = getTransform()->draw_position.x;
	const auto y = getTransform()->draw_position.y;

	
	switch (m_type)
	{
	case BD_CONSOLE:
		TextureManager::Instance()->draw("BossDecoConsole", x, y, 0, 255, false, SDL_FLIP_NONE);
		break;
	case BD_WINDOW:
		TextureManager::Instance()->draw("BossDecoWindow", x, y, 0, 255, false, SDL_FLIP_NONE);
		break;
	}
}

void BossDecoration::update()
{
}

void BossDecoration::clean()
{
}

void BossDecoration::setDestination(glm::vec2 destination)
{
}
