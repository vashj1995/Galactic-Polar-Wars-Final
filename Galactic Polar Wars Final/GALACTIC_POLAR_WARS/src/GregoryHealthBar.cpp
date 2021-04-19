#include "GregoryHealthBar.h"
#include "TextureManager.h"


GregoryHealthBar::GregoryHealthBar()
{
	TextureManager::Instance()->load("../Assets/textures/G-HP-0.png", "g0");
	TextureManager::Instance()->load("../Assets/textures/G-HP-01.png", "g1");
	TextureManager::Instance()->load("../Assets/textures/G-HP-02.png", "g2");
	TextureManager::Instance()->load("../Assets/textures/G-HP-03.png", "g3");
	TextureManager::Instance()->load("../Assets/textures/G-HP-04.png", "g4");
	TextureManager::Instance()->load("../Assets/textures/G-HP-05.png", "g5");
	TextureManager::Instance()->load("../Assets/textures/G-HP-06.png", "g6");
	TextureManager::Instance()->load("../Assets/textures/G-HP-07.png", "g7");
	TextureManager::Instance()->load("../Assets/textures/G-HP-08.png", "g8");
	TextureManager::Instance()->load("../Assets/textures/G-HP-09.png", "g9");
	TextureManager::Instance()->load("../Assets/textures/G-HP-10.png", "g10");
	TextureManager::Instance()->load("../Assets/textures/G-HP-11.png", "g11");
	TextureManager::Instance()->load("../Assets/textures/G-HP-12.png", "g12");
	TextureManager::Instance()->load("../Assets/textures/G-HP-13.png", "g13");
	TextureManager::Instance()->load("../Assets/textures/G-HP-14.png", "g14");
	TextureManager::Instance()->load("../Assets/textures/G-HP-15.png", "g15");
	TextureManager::Instance()->load("../Assets/textures/G-HP-16.png", "g16");
	TextureManager::Instance()->load("../Assets/textures/G-HP-17.png", "g17");
	const auto size = TextureManager::Instance()->getTextureSize("0");
	setWidth(size.x);
	setHeight(size.y);
	getTransform()->position = glm::vec2(430.0f, 120.0f);
	getRigidBody()->velocity = glm::vec2(0, 0);
	getRigidBody()->isColliding = false;

	m_gregoryHealth = 17;
}
GregoryHealthBar::~GregoryHealthBar()
= default;

void GregoryHealthBar::draw()
{

	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	switch (m_gregoryHealth)
	{
	case 0:
		TextureManager::Instance()->draw("g0", getTransform()->position.x, getTransform()->position.y, 0, 255, true);
		break;
	case 1:
		TextureManager::Instance()->draw("g1", getTransform()->position.x, getTransform()->position.y, 0, 255, true);
		break;
	case 2:
		TextureManager::Instance()->draw("g2", getTransform()->position.x, getTransform()->position.y, 0, 255, true);
		break;
	case 3:
		TextureManager::Instance()->draw("g3", getTransform()->position.x, getTransform()->position.y, 0, 255, true);
		break;
	case 4:
		TextureManager::Instance()->draw("g4", getTransform()->position.x, getTransform()->position.y, 0, 255, true);
		break;
	case 5:
		TextureManager::Instance()->draw("g5", getTransform()->position.x, getTransform()->position.y, 0, 255, true);
		break;
	case 6:
		TextureManager::Instance()->draw("g6", getTransform()->position.x, getTransform()->position.y, 0, 255, true);
		break;
	case 7:
		TextureManager::Instance()->draw("g7", getTransform()->position.x, getTransform()->position.y, 0, 255, true);
		break;
	case 8:
		TextureManager::Instance()->draw("g8", getTransform()->position.x, getTransform()->position.y, 0, 255, true);
		break;
	case 9:
		TextureManager::Instance()->draw("g9", getTransform()->position.x, getTransform()->position.y, 0, 255, true);
		break;
	case 10:
		TextureManager::Instance()->draw("g10", getTransform()->position.x, getTransform()->position.y, 0, 255, true);
		break;
	case 11:
		TextureManager::Instance()->draw("g11", getTransform()->position.x, getTransform()->position.y, 0, 255, true);
		break;
	case 12:
		TextureManager::Instance()->draw("g12", getTransform()->position.x, getTransform()->position.y, 0, 255, true);
		break;
	case 13:
		TextureManager::Instance()->draw("g13", getTransform()->position.x, getTransform()->position.y, 0, 255, true);
		break;
	case 14:
		TextureManager::Instance()->draw("g14", getTransform()->position.x, getTransform()->position.y, 0, 255, true);
		break;
	case 15:
		TextureManager::Instance()->draw("g15", getTransform()->position.x, getTransform()->position.y, 0, 255, true);
		break;
	case 16:
		TextureManager::Instance()->draw("g16", getTransform()->position.x, getTransform()->position.y, 0, 255, true);
		break;
	case 17:
		TextureManager::Instance()->draw("g17", getTransform()->position.x, getTransform()->position.y, 0, 255, true);
		break;
	}
}
void GregoryHealthBar::update()
{
	draw();
}

void GregoryHealthBar::clean()
{
}

void GregoryHealthBar::setHealthPointsUI(int pts)
{
	m_gregoryHealth = pts;
}