#include "LevelOne.h"
#include "Game.h"
#include "EventManager.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"
#include <cstdlib>
#include <ctime>

#include "Util.h"

LevelOne::LevelOne()
{
	// Load tile map & player/enemy spritesheet here.
	TextureManager::Instance()->loadTileMap(
		"../Assets/sprites/TileMapKey.txt",
		"../Assets/sprites/TileMap.png",
		"TileMap");

	TextureManager::Instance()->loadSpriteSheet(
		"../Assets/sprites/SpriteSheet.txt",
		"../Assets/sprites/SpriteSheet.png",
		"spritesheet");

	LevelOne::start();
}

LevelOne::~LevelOne()
= default;

void LevelOne::draw()
{
	if(EventManager::Instance().isIMGUIActive())
	{
		GUI_Function();
	}

	drawDisplayList();
	SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 255, 255, 255);

}

void LevelOne::update()
{
	if (m_reachedDoor)
		TheGame::Instance()->changeSceneState(LEVEL_TWO);
	
	if (m_gameOver)
		TheGame::Instance()->changeSceneState(END_SCENE);
	
	if(!m_reachedDoor && !m_gameOver)
	{
		updateDisplayList();
		updateDrawPositions();

		getTransform()->position = m_pPlayer->getTransform()->position - glm::vec2(640.0f, 800.0f * 3 / 4);

		// Incrementing timers.
		++m_shootTimer;
		++m_bearTimer;

		// So the player cannot get hit repeatedly. If hit recently, increment timer.
		// Reset timer & bool if a certain amount of time has passed.
		if(m_gotHitRecently)
		{
			if(m_invincibleTimer < 60)
				++m_invincibleTimer;
			if (m_invincibleTimer == 60)
			{
				m_invincibleTimer = 0;
				m_gotHitRecently = false;
			}
		}


		// So lava doesn't immediately drain Pigoo's HP. Or maybe it should.
		if(m_steppedInLava)
		{
			if (m_lavaTimer < 60)
				++m_lavaTimer;
			if(m_lavaTimer == 60)
			{
				m_lavaTimer = 0;
				m_steppedInLava = false;
			}
		}
		
		// So the player can't spam bullets unreasonably.
		if(m_shootTimer == 30)
		{
			m_shootTimer = 0;
			m_pPlayer->setShoot(true);
		}


		
		// Check collision between player & all 4 sides of the platform objects.
		for (unsigned i = 0; i < m_pTiles.size(); i++)
		{
			if (CollisionManager::AABBCheck(m_pPlayer, m_pTiles[i]) && !m_reachedDoor)
			{
				// If Pigoo collides with the door, transition to Level 2.
				if(m_pTiles[i]->getType() == TILE_DOOR)
				{
					m_reachedDoor = true;
				}
				
				// If Pigoo steps on a hazard tile, subtract a point of health and give him a tiny invincible window to get out.
				if(m_pTiles[i]->getType() == TILE_HAZARD && !m_steppedInLava)
				{
					m_pPlayer->setHealthPoints(false);
					m_pPlayer->getHit();
					m_pHPUI->setHealthPointsUI(m_pPlayer->getHealthPoints());
					m_steppedInLava = true;
				}
				
				// Bottom of the platform.
				if (m_pPlayer->getTransform()->draw_position.y - (float)m_pPlayer->getVelocityY() >= (m_pTiles[i]->getTransform()->draw_position.y + m_pTiles[i]->getHeight()))
				{
					m_pPlayer->setPosY(m_pTiles[i]->getTransform()->position.y + m_pTiles[i]->getHeight());
					m_pPlayer->stopMovingY();
				}
				else
				{
					if (m_pPlayer->getTransform()->draw_position.y - (float)m_pPlayer->getVelocityY() <= (m_pTiles[i]->getTransform()->draw_position.y - m_pTiles[i]->getHeight()))
					{
						m_pPlayer->setPosY(m_pTiles[i]->getTransform()->position.y - m_pTiles[i]->getHeight() - 10);
						m_pPlayer->stopMovingY();
						m_pPlayer->setMaxVelocityY(0);
						m_pPlayer->setGrounded(true);
					}
					else if (m_pPlayer->getTransform()->draw_position.x - (float)m_pPlayer->getVelocityX() <= (m_pTiles[i]->getTransform()->draw_position.x + m_pTiles[i]->getWidth()) && m_pPlayer->getFacingRight())
					{
						m_pPlayer->stopMovingX();
						//m_pPlayer->setAccelRateX(0);
						m_pPlayer->setPosX(m_pTiles[i]->getTransform()->position.x - m_pTiles[i]->getWidth() - 1);
					}
					else if (m_pPlayer->getTransform()->draw_position.x - (float)m_pPlayer->getVelocityX() >= (m_pTiles[i]->getTransform()->draw_position.x + m_pTiles[i]->getWidth()) && !m_pPlayer->getFacingRight())
					{
						m_pPlayer->stopMovingX();
						//m_pPlayer->setAccelRateX(0);
						m_pPlayer->setPosX(m_pTiles[i]->getTransform()->position.x + m_pTiles[i]->getWidth());
					}

				}
			}
		}
		
		
		// Check collision between Pigoo & each floor tile.
		for (unsigned i = 0; i < m_pFloorTiles.size(); i++)
		{
			if (CollisionManager::AABBCheck(m_pPlayer, m_pFloorTiles[i]) == true) // made similar to Platform collision check, so you don't fall through the floor on jumps.
			{
				m_pPlayer->stopMovingY();
				m_pPlayer->setMaxVelocityY(0);
				m_pPlayer->setPosY(m_pFloorTiles[i]->getTransform()->position.y - m_pFloorTiles[i]->getHeight() - 10);
				m_pPlayer->setGrounded(true);
			}
			else
			{
				m_pPlayer->setMaxVelocityY(15);
			}
		}
		
		// Checks collision against Pigoo & Alien Blaster sprite.
		// When they collide, switch to Alien Blaster mode.
		if(CollisionManager::AABBCheck(m_pPlayer, m_pAlienBlaster) == true)
		{
			removeChild(m_pAlienBlaster);
			SoundManager::Instance().playSound("pickup");
			m_pPlayer->setAlienBlaster(true);
			m_pWeaponUI[1]->setWeaponType(RMB_ALIEN_BLASTER);
		}

		// Checks collision against Pigoo and Fish sprite.
		// When they collide, removes fish from screen & increase Pigoo HP by 1.
		// Pigoo can't pick up the fish if he is full HP.
		if (!m_pFish.empty())
		{
			for (int i = 0; i < m_pFish.size(); i++)
			{
				if (CollisionManager::AABBCheck(m_pPlayer, m_pFish[i]) == true && m_pPlayer->getHealthPoints() < 5)
				{
					removeChild(m_pFish[i]);
					SoundManager::Instance().playSound("pickup");
					m_pPlayer->setHealthPoints(true);
					m_pHPUI->setHealthPointsUI(m_pPlayer->getHealthPoints());
				}
			}
		}

		// Check collision between Pigoo bullets & enemies.
		// Delete bullet & enemy upon collision.
		if(m_pEnemy.size() > 0 && m_pPlayerBullets.size() > 0)
		{
			for (unsigned i = 0; i < m_pEnemy.size(); i++)
			{
				for (unsigned j = 0; j < m_pPlayerBullets.size(); j++)
				{
					if (CollisionManager::circleAABBCheck(m_pPlayerBullets[j], m_pEnemy[i]) == true && !m_pEnemy[i]->isDead())
					{
						m_pEnemy[i]->setIsDead();
						removeChild(m_pPlayerBullets[j]);
						m_pPlayerBullets[j] = nullptr;
						m_pPlayerBullets.erase(m_pPlayerBullets.begin() + j);
						m_pPlayerBullets.shrink_to_fit();
					}
				}
			}
		}

		// Enemies each have their own death timer, handled by them. When it is complete, they will be removed from the scene.
		if(!m_pEnemy.empty())
		{
			for (int i = 0; i < m_pEnemy.size(); i++)
			{
				if(m_pEnemy[i]->isDeathTimerDone() && m_pEnemy[i]->isEnabled() == true)
				{
					m_pEnemy[i]->setEnabled(false);
					//removeChild(m_pEnemy[i]);
					//m_pEnemy[i] = nullptr;
					//m_pEnemy.erase(m_pEnemy.begin() + i);
					//m_pEnemy.shrink_to_fit();
				}
			}
		}
		
		if (m_pPlayer->isDead() == true)
		{
			m_playerDeathTimer++;

			if (m_playerDeathTimer >= 20)
			{
				m_playerDeathTimer = 0;
				m_gameOver = true;
			}
		}

		//Check Collision between Pigoo Bullets and Boxes
		if (m_pTiles.size() > 0 && m_pPlayerBullets.size() > 0)
		{
			for (unsigned i = 0; i < m_pTiles.size(); i++)
			{
				for (unsigned j = 0; j < m_pPlayerBullets.size(); j++)
				{
					if (CollisionManager::circleAABBCheck(m_pPlayerBullets[j], m_pTiles[i]) == true)
					{
						removeChild(m_pPlayerBullets[j]);
						m_pPlayerBullets[j] = nullptr;
						m_pPlayerBullets.erase(m_pPlayerBullets.begin() + j);
						m_pPlayerBullets.shrink_to_fit();
					}
				}
			}
		}

		// Check collision between Bear & Pigoo and decrement HP.
		if (!m_pEnemy.empty() && !m_invincibleTimer)
		{
			for (unsigned i = 0; i < m_pEnemy.size(); i++)
			{
				if (CollisionManager::circleAABBCheck(m_pPlayer, m_pEnemy[i]) == true && m_pEnemy[i]->isEnabled() == true)
				{
					if (m_gotHitRecently == false)
					{
						SoundManager::Instance().playSound("PHit");
						m_pPlayer->getHit();
						m_pPlayer->setHealthPoints(false);
						m_pHPUI->setHealthPointsUI(m_pPlayer->getHealthPoints());
					}
					m_gotHitRecently = true;
				}
			}
		}
		
		// Collision between Pigoo & enemy bullets and decrement HP.
		if (!m_pEnemyBullets.empty() && !m_invincibleTimer)
		{
			for (unsigned i = 0; i < m_pEnemyBullets.size(); i++)
			{
				if (CollisionManager::circleAABBCheck(m_pEnemyBullets[i], m_pPlayer) == true)
				{
					if (m_gotHitRecently == false)
					{
						SoundManager::Instance().playSound("PHit");
						m_pPlayer->getHit();
						m_pPlayer->setHealthPoints(false);
						m_pHPUI->setHealthPointsUI(m_pPlayer->getHealthPoints());
					}
					m_gotHitRecently = true;
					// Delete bullet if collision happens.
					removeChild(m_pEnemyBullets[i]);
					m_pEnemyBullets[i] = nullptr;
					m_pEnemyBullets.erase(m_pEnemyBullets.begin() + i);
					m_pEnemyBullets.shrink_to_fit();
				}
			}
		}

		//Check Collision between Enemy Bullets and Boxes
		if (m_pTiles.size() > 0 && m_pEnemyBullets.size() > 0)
		{
			for (unsigned i = 0; i < m_pTiles.size(); i++)
			{
				for (unsigned j = 0; j < m_pEnemyBullets.size(); j++)
				{
					if (CollisionManager::circleAABBCheck(m_pEnemyBullets[j], m_pTiles[i]) == true)
					{
						removeChild(m_pEnemyBullets[j]);
						m_pEnemyBullets[j] = nullptr;
						m_pEnemyBullets.erase(m_pEnemyBullets.begin() + j);
						m_pEnemyBullets.shrink_to_fit();
					}
				}
			}
		}


		// ENEMY BULLETS & TURNING TO FACE PIGOO ----------------------------------
		if(!m_pEnemy.empty())
		{
			for (unsigned i = 0; i < m_pEnemy.size(); i++)
			{
				bool direction;
				// Check if the enemy has a Blaster. If they do, make bullets.
				if(m_pEnemy[i]->hasIceBlaster() || m_pEnemy[i]->hasAlienBlaster() && !m_pEnemy[i]->isDead() && m_pEnemy[i]->isEnabled() == true)
				{
					if (Util::distance(m_pPlayer->getTransform()->position, m_pEnemy[i]->getTransform()->position) < 300.0f)
					{
						// Turn to face Pigoo in a certain range.
						if (m_pPlayer->getTransform()->position.x < m_pEnemy[i]->getTransform()->position.x )
						{
							direction = false;
							if(m_pEnemy[i]->hasIceBlaster())
								m_pEnemy[i]->setAnimationState(ENEMY_ICE_IDLE_LEFT);
							else
								m_pEnemy[i]->setAnimationState(ENEMY_AB_IDLE_LEFT);
						}
						else
						{
							direction = true;
							if (m_pEnemy[i]->hasIceBlaster())
								m_pEnemy[i]->setAnimationState(ENEMY_ICE_IDLE_RIGHT);
							else
								m_pEnemy[i]->setAnimationState(ENEMY_AB_IDLE_RIGHT);
						}
						// Increment the timer while Pigoo is in range.
						++m_enemyShootTimer;
						// The enemy can only shoot every 60 frames.
						// The >= is for if Pigoo goes out of range.
						if (m_enemyShootTimer >= 60)
						{
							m_enemyShootTimer = 0;
							// Shoot if Pigoo is at the same level (ish).
							if (m_pPlayer->getTransform()->position.y >= m_pEnemy[i]->getTransform()->position.y - m_pEnemy[i]->getHeight() && m_pPlayer->getTransform()->position.y <= m_pEnemy[i]->getTransform()->position.y + m_pEnemy[i]->getHeight())
							{
								// New bullet in Pigoo's direction.
								if(m_pEnemy[i]->hasIceBlaster())
								{
									m_pEnemyBullets.push_back(new BlasterBullet(glm::vec2(m_pEnemy[i]->getTransform()->position.x, m_pEnemy[i]->getTransform()->position.y - 7),
	                                direction, BlasterBullet::ICE));
								}
								else if(m_pEnemy[i]->hasAlienBlaster())
								{
									m_pEnemyBullets.push_back(new BlasterBullet(glm::vec2(m_pEnemy[i]->getTransform()->position.x, m_pEnemy[i]->getTransform()->position.y - 7),
	                                direction, BlasterBullet::ALIEN));
								}
								// AddChild the bullets so they will be drawn.
								for (unsigned i = 0; i < m_pEnemyBullets.size(); i++)
								{
									addChild(m_pEnemyBullets[i], 3);
								}
							}
						}
					}				
				}
			}
		}

		// Delete player bullets if they go off screen.
		if(!m_pPlayerBullets.empty())
		{
			for (unsigned i = 0; i < m_pPlayerBullets.size(); i++)
			{
				if(m_pPlayerBullets[i]->getTransform()->position.x < (m_pPlayer->getTransform()->position.x - Config::SCREEN_WIDTH / 2) || m_pPlayerBullets[i]->getTransform()->position.x >(m_pPlayer->getTransform()->position.x + Config::SCREEN_WIDTH / 2))
				{
					removeChild(m_pPlayerBullets[i]);
					m_pPlayerBullets[i] = nullptr;
					m_pPlayerBullets.erase(m_pPlayerBullets.begin() + i);
					m_pPlayerBullets.shrink_to_fit();
				}
			}
		}

		// Delete enemy bullets if they go off screen.
		if(!m_pEnemyBullets.empty())
		{
			for (unsigned i = 0; i < m_pEnemyBullets.size(); i++)
			{
				if(m_pEnemyBullets[i]->getTransform()->position.x < (m_pPlayer->getTransform()->position.x - Config::SCREEN_WIDTH/2) || m_pEnemyBullets[i]->getTransform()->position.x >(m_pPlayer->getTransform()->position.x + Config::SCREEN_WIDTH / 2))
				{
					removeChild(m_pEnemyBullets[i]);
					m_pEnemyBullets[i] = nullptr;
					m_pEnemyBullets.erase(m_pEnemyBullets.begin() + i);
					m_pEnemyBullets.shrink_to_fit();
				}
			}
		}
		
	}
}

void LevelOne::clean()
{
	SoundManager::Instance().unload("bkg", SOUND_MUSIC);


	removeAllChildren();
	//m_pEnemy.clear();
}

void LevelOne::handleEvents()
{
	if(m_reachedDoor == false)
		EventManager::Instance().update();
	
	//COORDINATE GETTER
	if (EventManager::Instance().getMouseButton(1))
	{
		std::cout << " ||| X Coordinate :: " << EventManager::Instance().getMousePosition().x + getTransform()->position.x << " |||" << std::endl;
		std::cout << " ||| Y Coordinate :: " << EventManager::Instance().getMousePosition().y + getTransform()->position.y << " |||" << std::endl;
	}

	// If player is able to shoot, spawn a bullet when RMB is pressed.
	if (EventManager::Instance().getMouseButton(2))
	{
		if (m_pPlayer->getAlienBlaster() == true && m_pPlayer->canShoot() == true)
		{
			SoundManager::Instance().playSound("Blaster");
			m_pPlayer->setShoot(false);
			m_pPlayerBullets.push_back(new BlasterBullet(glm::vec2(m_pPlayer->getTransform()->position.x, m_pPlayer->getTransform()->position.y - 4), m_pPlayer->getFacingRight(), BlasterBullet::ALIEN));
			for (unsigned i = 0; i < m_pPlayerBullets.size(); i++)
			{
				addChild(m_pPlayerBullets[i], 3);
			}
		}
	}

	// Melee combat & enemy distance check.
	if (EventManager::Instance().getMouseButton(0))
	{
		m_pPlayer->meleeAttack();

		if(!m_pEnemy.empty())
		{
			for (int i = 0; i < m_pEnemy.size(); i++)
			{
				if (Util::distance(m_pPlayer->getTransform()->position, m_pEnemy[i]->getTransform()->position) < 60 && m_pEnemy[i]->isEnabled() == true)
				{
					m_pEnemy[i]->setIsDead();
				}
			}
		}
	}



	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_0))
	{
		TheGame::Instance()->changeSceneState(START_SCENE);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_P))
	{
		TheGame::Instance()->changeSceneState(PAUSE_SCENE);
	}

	// FOR TESTING
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_B))
	{
		TheGame::Instance()->changeSceneState(BOSS_LEVEL);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_G))
	{
		TheGame::Instance()->changeSceneState(LEVEL_TWO);
	}
}

void LevelOne::start()
{
	// Seed rand() with the time.
	const unsigned int kRandSeed = time(0);
	srand(kRandSeed);

	// Music:
	SoundManager::Instance().load("../assets/audio/Industrial_crop.mp3", "bkg", SOUND_MUSIC);
	SoundManager::Instance().load("../assets/audio/Pickup.wav", "pickup", SOUND_SFX);
	SoundManager::Instance().load("../assets/audio/Alien_Death.wav", "ADeath", SOUND_SFX);
	SoundManager::Instance().load("../assets/audio/Alien_Hit.wav", "AHit", SOUND_SFX);
	SoundManager::Instance().load("../assets/audio/Pain_noot.wav", "PHit", SOUND_SFX);
	SoundManager::Instance().load("../assets/audio/Blaster.wav", "Blaster", SOUND_SFX);
	SoundManager::Instance().playMusic("bkg");								

	// Set GUI Title
	m_guiTitle = "Freezer";

	// Player ------------------
	m_pPlayer = new Player();
	m_pPlayer->setFacingRight(true);
	addChild(m_pPlayer, 4);
	// End of Player -----------

	// Start of Level/Platform ----------------------------
	// Create new Level & add platforms(tiles).
	m_pFreezerLevel = new Level(87, 19, FREEZER);
	m_pFreezerLevel->addTiles(m_pTiles, m_pDecorations);
	addChild(m_pFreezerLevel, 8);

	for (unsigned i = 0; i < m_pTiles.size(); i++)
	{
		addChild(m_pTiles[i], 3);
	}

	for (unsigned i = 0; i < m_pDecorations.size(); i++)
	{
		addChild(m_pDecorations[i], 2);
	}
	// End of Level/Platform ----------------------------

	// Start of Enemies ---------------------------------------------------------------------------------------------------------------------------------------------------------

	//Bears before walls.
	m_pEnemy.push_back(new Enemy(glm::vec2(490.0f, 90.0f), Enemy::ALIEN)); 
	m_pEnemy.push_back(new Enemy(glm::vec2(125.0f, 90.0f), Enemy::ALIEN));
	m_pEnemy.push_back(new Enemy(glm::vec2(1160.0f, 130.0f), Enemy::ALIEN));
	m_pEnemy.push_back(new Enemy(glm::vec2(1520.0f, 330.0f), Enemy::ALIEN));
	m_pEnemy.push_back(new Enemy(glm::vec2(1360.0f, 450.0f), Enemy::ALIEN));
	m_pEnemy.push_back(new Enemy(glm::vec2(1780.0f, 570.0f), Enemy::ALIEN));

	//Bears after walls.
	m_pEnemy.push_back(new Enemy(glm::vec2(2131.0f, 410.0f), Enemy::ALIEN));
	m_pEnemy.push_back(new Enemy(glm::vec2(2672.0f, 370.0f), Enemy::ALIEN));
	m_pEnemy.push_back(new Enemy(glm::vec2(3056.0f, 650.0f), Enemy::ALIEN));
	m_pEnemy.push_back(new Enemy(glm::vec2(2782.0f, 210.0f), Enemy::ALIEN));
	m_pEnemy.push_back(new Enemy(glm::vec2(3148.0f, 210.0f), Enemy::ALIEN));
	m_pEnemy.shrink_to_fit();



	for (unsigned i = 0; i < m_pEnemy.size(); i++)
	{
		addChild(m_pEnemy[i], 5);
	}

	// End of Enemies ------------------------------------------------------------------------------------------------------------------------------------------------------------

	// Item Setup -------------------------------------------------------------------------
	// Fish Item:
	m_pFish.push_back(new Fish());
	m_pFish[0]->getTransform()->position = glm::vec2(300.0f, 230.0f);

	m_pFish.push_back(new Fish());
	m_pFish[1]->getTransform()->position = glm::vec2(359.65f, 430.0f);

	m_pFish.push_back(new Fish());
	m_pFish[2]->getTransform()->position = glm::vec2(1329.5f, 70.0f);

	m_pFish.push_back(new Fish());
	m_pFish[3]->getTransform()->position = glm::vec2(904.0f, 110.0f);

	m_pFish.push_back(new Fish());
	m_pFish[4]->getTransform()->position = glm::vec2(2634.0f, 390.0f);

	m_pFish.push_back(new Fish());
	m_pFish[5]->getTransform()->position = glm::vec2(3359.0f, 550.0f);

	for (Fish* fish : m_pFish)
	{
		addChild(fish, 2);
	}


	// Alien Blaster Item:
	m_pAlienBlaster = new AlienBlaster();
	m_pAlienBlaster->getTransform()->position = glm::vec2(600.0f, 310.0f);
	addChild(m_pAlienBlaster, 2);
	// End of Items -----------------------------------------------------------------------

	

	// Floor Tile Setup -------------------------------------------------------------------
	// We still need the Floor tiles for the gravity to work. Until a workaround is figured out,
	// the Floor Tiles are still there but not rendered.

	for (int i = 0; i <= 75; i++)
	{
		// Random number from 1-10 for the FloorType. To make it more interesting, visually.
		int altFloor = rand() % 10 + 1;

		// If even do FloorType 1:
		if (altFloor % 2 == 0)
		{
			m_pFloorTiles.push_back(new Floor(glm::vec2((40 * i) + 20, 5000.0f), FF1));
		}
		// Else, odd, FloorType 2:
		else
		{
			m_pFloorTiles.push_back(new Floor(glm::vec2((40 * i) + 20, 5000.0f), FF2));
		}
		// AddChild the Floor.
		addChild(m_pFloorTiles[i], 2);
		m_pFloorTiles[i]->setEnabled(false);
	}
	// End of Floor Tile Setup -------------------------------------------------------------

	// Background--------------------------
	m_pFreezeBackground = new FreezerBackground();
	addChild(m_pFreezeBackground, 1);
	//End of Background -------------------

	// UI--------------------------
	m_pHPUI = new HealthUI();
	m_pHPUI->getTransform()->position = glm::vec2(120.0f, 40.0f);
	addChild(m_pHPUI, 5);

	m_pWeaponUI.push_back(new WeaponUI(LMB_ICICLE, glm::vec2(60.0f, m_pHPUI->getTransform()->position.y + m_pHPUI->getHeight() + 20)));
	addChild(m_pWeaponUI[0], 5);
	m_pWeaponUI.push_back(new WeaponUI(RMB_UNARMED, glm::vec2(60.0f + m_pWeaponUI[0]->getWidth() + 20, m_pHPUI->getTransform()->position.y + m_pHPUI->getHeight()  + 20)));
	addChild(m_pWeaponUI[1], 5);

	
	//End of UI -------------------
}

// IMGUI --------------------------------
void LevelOne::GUI_Function() const
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();
	
	ImGui::Begin("Your Window Title Goes Here", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);

	if(ImGui::Button("My Button"))
	{
		std::cout << "My Button Pressed" << std::endl;
	}

	ImGui::Separator();

	static float float3[3] = { 0.0f, 1.0f, 1.5f };
	if(ImGui::SliderFloat3("My Slider", float3, 0.0f, 2.0f))
	{
		std::cout << float3[0] << std::endl;
		std::cout << float3[1] << std::endl;
		std::cout << float3[2] << std::endl;
		std::cout << "---------------------------\n";
	}

	ImGui::SameLine(350);

	static bool check;
	ImGui::Checkbox("My Checkbox", &check);
	
	ImGui::End();

	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}

