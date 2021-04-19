#include "WinScene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"

WinScene::WinScene()
{
	WinScene::start();
}

WinScene::~WinScene()
= default;

void WinScene::draw()
{
	drawDisplayList();
}

void WinScene::update()
{
	updateDisplayList();
}

void WinScene::clean()
{
	SoundManager::Instance().unload("sawwy", SOUND_MUSIC);

	removeAllChildren();
}

void WinScene::handleEvents()
{
	EventManager::Instance().update();

	// Keyboard Events
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(START_SCENE);
	}
}

void WinScene::start()
{
	SoundManager::Instance().load("../Assets/audio/Sawwy.mp3", "sawwy", SOUND_MUSIC);
	SoundManager::Instance().playMusic("sawwy");

	//TEXT COLORS----
	const SDL_Color blue = { 0, 0, 255, 255 };
	const SDL_Color red = { 255, 0, 0, 255 };
	//END OF TEXT COLORS----

	//BACKGROUND---
	m_pWinBackground = new SpaceBackground(SpaceBkgType::SPACE_WIN);
	addChild(m_pWinBackground, 1);
	//END OF BACKGROUND---

	//BUTTONS---
	// Restart Button
	m_pRestartButton = new Button("../Assets/textures/restartButton.png", "restartButton", RESTART_BUTTON, glm::vec2(150.0f, 300.0f), true);
	
	m_pRestartButton->addEventListener(CLICK, [&]()-> void
		{
			m_pRestartButton->setActive(false);
			TheGame::Instance()->changeSceneState(START_SCENE);
		});

	m_pRestartButton->addEventListener(MOUSE_OVER, [&]()->void
		{
			m_pRestartButton->setAlpha(128);
		});

	m_pRestartButton->addEventListener(MOUSE_OUT, [&]()->void
		{
			m_pRestartButton->setAlpha(255);
		});

	addChild(m_pRestartButton, 2);
	//END OF BUTTONS ---
}
