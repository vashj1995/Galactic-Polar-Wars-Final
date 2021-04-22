#include "PauseScene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"

PauseScene::PauseScene()
{
	PauseScene::start();
}

PauseScene::~PauseScene()
= default;

void PauseScene::draw()
{
	drawDisplayList();
}

void PauseScene::update()
{
	updateDisplayList();
}

void PauseScene::clean()
{
	removeAllChildren();
}

void PauseScene::handleEvents()
{
	EventManager::Instance().update();

	// Keyboard Events
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_R))
	{
		TheGame::Instance()->changeSceneState(LEVEL_ONE);
	}
}

void PauseScene::start()
{
	//TEXT COLORS
	const SDL_Color blue = { 0, 0, 255, 255 };
	const SDL_Color red = { 255, 0, 0, 255 };
	//END OF TEXT COLORS

	//BACKGROUND---
	m_pPauseBackground = new TitleBackground();
	addChild(m_pPauseBackground, 1);
	//END OF BACKGROUND---

	//BUTTONS---
	// Resume Button
	m_pPauseButtons.push_back(new Button("../Assets/textures/ResumeButton.png", "ResumeButton", RESUME_BUTTON, glm::vec2(640.0f, 450.0f), true));
	m_pPauseButtons[0]->addEventListener(CLICK, [&]()-> void
		{
			m_pPauseButtons[0]->setActive(false);
			TheGame::Instance()->changeSceneState(LEVEL_ONE);
		});

	m_pPauseButtons[0]->addEventListener(MOUSE_OVER, [&]()->void
		{
			m_pPauseButtons[0]->setAlpha(200);
		});

	m_pPauseButtons[0]->addEventListener(MOUSE_OUT, [&]()->void
		{
			m_pPauseButtons[0]->setAlpha(255);
		});
	addChild(m_pPauseButtons[0], 2);

	//// Exit Button
	m_pPauseButtons.push_back(new Button("../Assets/textures/ExitButton.png", "ExitButton", EXIT_BUTTON, glm::vec2(640.0f, m_pPauseButtons[0]->getTransform()->position.y + 65), true));
	m_pPauseButtons[1]->addEventListener(CLICK, [&]()-> void
		{
			m_pPauseButtons[1]->setActive(false);
			TheGame::Instance()->changeSceneState(END_SCENE);
		});

	m_pPauseButtons[1]->addEventListener(MOUSE_OVER, [&]()->void
		{
			m_pPauseButtons[1]->setAlpha(200);
		});

	m_pPauseButtons[1]->addEventListener(MOUSE_OUT, [&]()->void
		{
			m_pPauseButtons[1]->setAlpha(255);
		});
	addChild(m_pPauseButtons[1], 2);
	////END OF BUTTONS----

}