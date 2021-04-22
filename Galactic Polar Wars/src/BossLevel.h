#pragma once
#ifndef __BOSS_LEVEL__
#define __BOSS_LEVEL__

#include "Scene.h"
#include "Player.h"
#include "Enemy.h"
#include "Gregory.h"
#include "Platform.h"
#include "EngineBackground.h"
#include "Label.h"
#include "SoundManager.h"
#include <vector>

#include "AlienBlaster.h"
#include "BlasterBullet.h"
#include "BossDecoration.h"
#include "GregoryBullet.h"
#include "Fish.h"
#include "Floor.h"
#include "HealthUI.h"
#include "GregoryHealthBar.h"
#include "Level.h"
#include "WeaponUI.h"

class BossLevel : public Scene
{
public:
	BossLevel();
	~BossLevel();

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

	EngineBackground* m_pEngineBackground;

	// Player:
	Player* m_pPlayer;
	HealthUI* m_pHPUI;
	std::vector<WeaponUI*> m_pWeaponUI;
	// Short timer so collision doesn't kill the player instantly.
	int m_invincibleTimer;
	int m_gregoryAngryTimer;
	bool m_gotHitRecently;
	bool m_gregoryHitRecently;

	// Enemies:
	std::vector<Enemy*> m_pEnemy;
	int m_gregoryShootTimer,
		m_enemyShootTimer;
	int m_bearTimer;

	// Boss:
	Gregory* m_pGregory;
	GregoryHealthBar* m_pGregHealth;

	// Items:
	std::vector<Fish*> m_pFish;
	std::vector<BlasterBullet*> m_pPlayerBullets;
	std::vector<BlasterBullet*> m_pEnemyBullets;
	std::vector<GregoryBullet*> m_pGregoryBullets;

	std::vector<BossDecoration*> m_pBossDecos;

	// Tiles:
	Level* m_pBossLevel;
	std::vector<DisplayObject*> m_pTiles;
	std::vector<DisplayObject*> m_pDecorations;
	std::vector<Floor*> m_pFloorTiles;

	bool m_gameOver = false,
	m_gameWon = false;
	
	int m_shootTimer = 0;

	int m_playerDeathTimer = 0;

	bool m_steppedInLava = false;
	int m_lavaTimer = 0;
};

#endif  /*defined (__BOSS_LEVEL__) */
