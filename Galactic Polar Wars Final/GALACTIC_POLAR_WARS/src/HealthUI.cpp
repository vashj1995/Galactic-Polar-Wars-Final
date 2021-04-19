#include "HealthUI.h"
#include "TextureManager.h"


HealthUI::HealthUI()
{
	TextureManager::Instance()->load("../Assets/textures/HealthBar_0.png", "0");
	TextureManager::Instance()->load("../Assets/textures/HealthBar_1.png", "1");
	TextureManager::Instance()->load("../Assets/textures/HealthBar_2.png", "2");
	TextureManager::Instance()->load("../Assets/textures/HealthBar_3.png", "3");
	TextureManager::Instance()->load("../Assets/textures/HealthBar_4.png", "4");
	TextureManager::Instance()->load("../Assets/textures/HealthBar_5.png", "5");
	const auto size = TextureManager::Instance()->getTextureSize("0");
	setWidth(size.x);
	setHeight(size.y);
	getTransform()->position = glm::vec2(430.0f, 120.0f);
	getRigidBody()->velocity = glm::vec2(0, 0);
	getRigidBody()->isColliding = false;

	m_healthPointsUI = 5;
}
HealthUI::~HealthUI()
= default;

void HealthUI::draw()
{

	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	switch (m_healthPointsUI)
	{
	case 0:
		TextureManager::Instance()->draw("0", getTransform()->position.x, getTransform()->position.y, 0, 255, true);
		break;
	case 1:
		TextureManager::Instance()->draw("1", getTransform()->position.x, getTransform()->position.y, 0, 255, true);
		break;
	case 2:
		TextureManager::Instance()->draw("2", getTransform()->position.x, getTransform()->position.y, 0, 255, true);
		break;
	case 3:
		TextureManager::Instance()->draw("3", getTransform()->position.x, getTransform()->position.y, 0, 255, true);
		break;
	case 4:
		TextureManager::Instance()->draw("4", getTransform()->position.x, getTransform()->position.y, 0, 255, true);
		break;
	case 5:
		TextureManager::Instance()->draw("5", getTransform()->position.x, getTransform()->position.y, 0, 255, true);
		break;
	}
}
void HealthUI::update()
{
	draw();
}

void HealthUI::clean()
{
}

void HealthUI::setHealthPointsUI(int pts)
{
	m_healthPointsUI = pts;
}

