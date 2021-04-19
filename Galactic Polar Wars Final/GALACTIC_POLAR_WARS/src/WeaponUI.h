#pragma once
#ifndef __WEAPONUI__
#define __WEAPONUI__
#include "DisplayObject.h"
#include "WeaponType.h"

class WeaponUI : public DisplayObject
{
public:
	WeaponUI(WeaponType type, glm::vec2 position);
	~WeaponUI();

	// Inherited from DisplayObject.
	void draw() override;
	void update() override;
	void clean() override;

	void setAmmoCount(int ammo);
	void setWeaponType(WeaponType type);

private:
	int m_ammo;
	WeaponType m_weaponType;
};

#endif
