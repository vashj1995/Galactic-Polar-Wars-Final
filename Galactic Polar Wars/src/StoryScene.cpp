#include "StoryScene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"

StoryScene::StoryScene()
{
	StoryScene::start();
}

StoryScene::~StoryScene()
= default;

void StoryScene::draw()
{
	drawDisplayList();
}

void StoryScene::update()
{
	//Starts playing main loop when riser stops.
	if (SoundManager::Instance().checkMusic() == 0)
	{
		std::cout << "\nStart loop";
		SoundManager::Instance().playMusic("PWell_loop", -1, 0);
	}

	updateDisplayList();
}

void StoryScene::clean()
{
	removeAllChildren();
}

void StoryScene::handleEvents()
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

void StoryScene::start()
{
	//TEXT COLORS
	const SDL_Color blue = { 0, 0, 255, 255 };
	const SDL_Color red = { 255, 0, 0, 255 };
	//END OF TEXT COLORS

	//BACKGROUND---
	m_pStoryBackground = new StoryBackground();
	addChild(m_pStoryBackground, 1);
	//END OF BACKGROUND---

	//BUTTONS---
	// Start Button
	m_pStoryButtons.push_back(new Button("../Assets/textures/NewButton.png", "StartButton", START_BUTTON, glm::vec2(250.0f, 300.0f), true));

	m_pStoryButtons[0]->addEventListener(CLICK, [&]()-> void
		{
			m_pStoryButtons[0]->setActive(false);
			TheGame::Instance()->changeSceneState(LEVEL_ONE);
		});

	m_pStoryButtons[0]->addEventListener(MOUSE_OVER, [&]()->void
		{
			m_pStoryButtons[0]->setAlpha(200);
		});

	m_pStoryButtons[0]->addEventListener(MOUSE_OUT, [&]()->void
		{
			m_pStoryButtons[0]->setAlpha(255);
		});
	addChild(m_pStoryButtons[0], 2);

	// Back Button
	m_pStoryButtons.push_back(new Button("../Assets/textures/BackButton.png", "BackButton", BACK_BUTTON, glm::vec2(250.0f, m_pStoryButtons[0]->getTransform()->position.y + 65), true));
	m_pStoryButtons[1]->addEventListener(CLICK, [&]()-> void
		{
			m_pStoryButtons[1]->setActive(false);
			TheGame::Instance()->changeSceneState(START_SCENE);
		});

	m_pStoryButtons[1]->addEventListener(MOUSE_OVER, [&]()->void
		{
			m_pStoryButtons[1]->setAlpha(200);
		});

	m_pStoryButtons[1]->addEventListener(MOUSE_OUT, [&]()->void
		{
			m_pStoryButtons[1]->setAlpha(255);
		});
	addChild(m_pStoryButtons[1], 2);

	//END OF BUTTONS----

}