#pragma once
#ifndef __LEVEL_ONE__
#define __LEVEL_ONE__

#include "Scene.h"
#include "Player.h"
#include "Enemy.h"
#include "Platform.h"
#include "FreezerBackground.h"
#include "Label.h"
#include "SoundManager.h"
#include <vector>

#include "AlienBlaster.h"
#include "BlasterBullet.h"
#include "Fish.h"
#include "Floor.h"
#include "HealthUI.h"
#include "Level.h"
#include "WeaponUI.h"

class LevelOne : public Scene
{
public:
	LevelOne();
	~LevelOne();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;

private:
	// IMGUI Function
	void GUI_Function() const;

	std::string m_guiTitle;
	
	glm::vec2 m_mousePosition;

	FreezerBackground* m_pFreezeBackground;

	// Player:
	Player* m_pPlayer;
	HealthUI* m_pHPUI;
	std::vector<WeaponUI*> m_pWeaponUI;
	// Short timer so collision doesn't kill the player instantly.
	int m_invincibleTimer;
	bool m_gotHitRecently;
	bool m_steppedInLava;
	int m_lavaTimer;

	bool m_reachedDoor = false;
	bool m_gameOver = false;

	// Items:
	std::vector<Fish*> m_pFish;
	AlienBlaster* m_pAlienBlaster;
	std::vector<BlasterBullet*> m_pPlayerBullets;
	std::vector<BlasterBullet*> m_pEnemyBullets;

	// Tiles:
	//std::vector<Platform*> m_pPlatforms;
	Level* m_pFreezerLevel;
	std::vector<DisplayObject*> m_pTiles;
	std::vector<DisplayObject*> m_pDecorations;
	std::vector<Floor*> m_pFloorTiles;

	// Enemies:
	std::vector<Enemy*> m_pEnemy;
	int m_enemyShootTimer;

	int m_shootTimer;
	int m_bearTimer;
	int m_playerDeathTimer;
	
};

#endif  /*defined (__LEVEL_ONE__) */