#include "EndScene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"

EndScene::EndScene()
{
	EndScene::start();
}

EndScene::~EndScene()
= default;

void EndScene::draw()
{
	drawDisplayList();
}

void EndScene::update()
{
	updateDisplayList();
}

void EndScene::clean()
{
	SoundManager::Instance().unload("likey", SOUND_MUSIC);
	removeAllChildren();
}

void EndScene::handleEvents()
{
	EventManager::Instance().update();

	// Keyboard Events
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(LEVEL_ONE);
	}
}

void EndScene::start()
{
	SoundManager::Instance().load("../Assets/audio/Likey_cut.mp3", "likey", SOUND_MUSIC);
	SoundManager::Instance().playMusic("likey");

	//TEXT COLORS----
	const SDL_Color blue = { 0, 0, 255, 255 };
	const SDL_Color red = { 255, 0, 0, 255 };
	//END OF TEXT COLORS----

	//BACKGROUND---
	m_pEndBackground = new SpaceBackground(SpaceBkgType::SPACE_LOSE);
	addChild(m_pEndBackground, 1);
	//END OF BACKGROUND---

	//BUTTONS---
	// Restart Button
	m_pRestartButton = new Button("../Assets/textures/restartButton.png", "restartButton", RESTART_BUTTON, glm::vec2(640.0f, 320.0f), true);

	m_pRestartButton->addEventListener(CLICK, [&]()-> void
	{
		m_pRestartButton->setActive(false);
		TheGame::Instance()->changeSceneState(LEVEL_ONE);
	});

	m_pRestartButton->addEventListener(MOUSE_OVER, [&]()->void
	{
		m_pRestartButton->setAlpha(128);
	});

	m_pRestartButton->addEventListener(MOUSE_OUT, [&]()->void
	{
		m_pRestartButton->setAlpha(255);
	});

	addChild(m_pRestartButton, 3);
	//END OF BUTTONS ---
}
