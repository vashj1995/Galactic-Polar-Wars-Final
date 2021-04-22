#include "WeaponUI.h"

#include "TextureManager.h"

WeaponUI::WeaponUI(WeaponType type, glm::vec2 position)
{
	this->getTransform()->position = position;
	TextureManager::Instance()->load("../Assets/textures/UI_LMB_Empty.png", "lmb_unarmed");
	TextureManager::Instance()->load("../Assets/textures/UI_RMB_Empty.png", "rmb_unarmed");
	TextureManager::Instance()->load("../Assets/textures/UI_RMB_AB.png", "rmb_alien_blaster");
	TextureManager::Instance()->load("../Assets/textures/UI_LMB_Icicle.png", "lmb_icicle");

	const auto size = TextureManager::Instance()->getTextureSize("lmb_unarmed");
	setWidth(size.x);
	setHeight(size.y);
	getRigidBody()->velocity = glm::vec2(0, 0);
	getRigidBody()->isColliding = false;

	m_weaponType = type;
}

WeaponUI::~WeaponUI() = default;

void WeaponUI::draw()
{
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	switch (m_weaponType)
	{
	case LMB_UNARMED:
		TextureManager::Instance()->draw("lmb_unarmed", getTransform()->position.x, getTransform()->position.y, 0, 255, true);
		break;
	case RMB_UNARMED:
		TextureManager::Instance()->draw("rmb_unarmed", getTransform()->position.x, getTransform()->position.y, 0, 255, true);
		break;
	case RMB_ALIEN_BLASTER:
		TextureManager::Instance()->draw("rmb_alien_blaster", getTransform()->position.x, getTransform()->position.y, 0, 255, true);
		break;
	case LMB_ICICLE:
		TextureManager::Instance()->draw("lmb_icicle", getTransform()->position.x, getTransform()->position.y, 0, 255, true);
		break;
	}

}

void WeaponUI::update()
{
	draw();
}

void WeaponUI::clean()
{
}

void WeaponUI::setAmmoCount(int ammo)
{
	m_ammo = ammo;
}

void WeaponUI::setWeaponType(WeaponType type)
{
	m_weaponType = type;
}
