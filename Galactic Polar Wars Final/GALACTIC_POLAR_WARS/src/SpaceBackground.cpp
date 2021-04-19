#include "SpaceBackground.h"

SpaceBackground::SpaceBackground()
{
	TextureManager::Instance()->load("../Assets/textures/SpaceBackground.png", "SpaceBackground");

	auto size = TextureManager::Instance()->getTextureSize("SpaceBackground");
	setWidth(1280);
	setHeight(800);
	setEnabled(true);
	setType(BACKGROUND1);
	m_spaceBkgType = SPACE_REG;
}

SpaceBackground::SpaceBackground(SpaceBkgType type)
{
	m_spaceBkgType = type;

	if(m_spaceBkgType == SPACE_WIN)
	{
		TextureManager::Instance()->load("../Assets/textures/winBkg.png", "winBkg");
	}
	else if(m_spaceBkgType == SPACE_LOSE)
	{
		TextureManager::Instance()->load("../Assets/textures/loseBkg.png", "loseBkg");
	}
	
	setWidth(1280);
	setHeight(800);
	setEnabled(true);
}

SpaceBackground::~SpaceBackground()
= default;

void SpaceBackground::draw()
{
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;
	switch (m_spaceBkgType)
	{
	case SPACE_REG:
		TextureManager::Instance()->draw("SpaceBackground", 0, 0, 0, 255, false, SDL_FLIP_NONE);
		break;
	case SPACE_WIN:
		TextureManager::Instance()->draw("winBkg", 0, 0, 0, 255, false, SDL_FLIP_NONE);
		break;
	case SPACE_LOSE:
		TextureManager::Instance()->draw("loseBkg", 0, 0, 0, 255, false, SDL_FLIP_NONE);
		break;
	}
	//getTransform()->position.x, getTransform()->position.y, 255, true);
}

void SpaceBackground::update()
{

}

void SpaceBackground::clean()
{
}

void SpaceBackground::setDestination(const glm::vec2 destination)
{
	//m_destination = destination;
}
