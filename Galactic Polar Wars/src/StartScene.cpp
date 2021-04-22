#include "StartScene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"

StartScene::StartScene()
{
	StartScene::start();
}

StartScene::~StartScene()
= default;

void StartScene::draw()
{
	drawDisplayList();
}

void StartScene::update()
{
	updateDisplayList();
}

void StartScene::clean()
{
	removeAllChildren();
}

void StartScene::handleEvents()
{
	EventManager::Instance().update();

	//Starts playing main loop when riser stops.
	if (SoundManager::Instance().checkMusic() == 0)						 
	{																	 
		std::cout << "\nStart loop";									 
		SoundManager::Instance().playMusic("PWell_loop", -1, 0);		 
	}

	//music volume, lowered
	SoundManager::Instance().setMusicVolume(3); 

	// Keyboard Events
	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(LEVEL_ONE);
	}
}

void StartScene::start()
{
	//START OF MUSIC----
	//loading Riser
	SoundManager::Instance().load("../Assets/audio/PWell_rise.mp3", "PWell_rise", SOUND_MUSIC); 

	//loading main loop
	SoundManager::Instance().load("../Assets/audio/PWell_loop.mp3", "PWell_loop", SOUND_MUSIC); 

	//panning
	SoundManager::Instance().panSet(48, -1);

	//playing the riser
	if (SoundManager::Instance().checkMusic() == 0)
	{
		SoundManager::Instance().playMusic("PWell_rise", 0, 0);
	}
	//END MUSIC----


	//TEXT COLORS
	const SDL_Color blue = { 0, 0, 255, 255 };
	const SDL_Color red = { 255, 0, 0, 255 }; 
	//END OF TEXT COLORS

	//BACKGROUND---
	m_pTitleBackground = new TitleBackground();
	addChild(m_pTitleBackground, 1);
	//END OF BACKGROUND---

	//BUTTONS---
	// Start Button
	m_pMenuButtons.push_back(new Button("../Assets/textures/startButton.png", "StartButton", START_BUTTON, glm::vec2(640.0f,430.0f), true));
	
	m_pMenuButtons[0]->addEventListener(CLICK, [&]()-> void
	{
		m_pMenuButtons[0]->setActive(false);
		TheGame::Instance()->changeSceneState(LEVEL_ONE);
	});
	
	m_pMenuButtons[0]->addEventListener(MOUSE_OVER, [&]()->void
	{
		m_pMenuButtons[0]->setAlpha(200);
	});

	m_pMenuButtons[0]->addEventListener(MOUSE_OUT, [&]()->void
	{
		m_pMenuButtons[0]->setAlpha(255);
	});
	addChild(m_pMenuButtons[0],2);

	// Story Synopsis Button
	m_pMenuButtons.push_back(new Button("../Assets/textures/StoryButton.png", "StoryButton", STORY_BUTTON, glm::vec2(640.0f, m_pMenuButtons[0]->getTransform()->position.y + 65), true));
	m_pMenuButtons[1]->addEventListener(CLICK, [&]()-> void
		{
			m_pMenuButtons[1]->setActive(false);
			TheGame::Instance()->changeSceneState(STORY_SCENE);
		});

	m_pMenuButtons[1]->addEventListener(MOUSE_OVER, [&]()->void
		{
			m_pMenuButtons[1]->setAlpha(200);
		});

	m_pMenuButtons[1]->addEventListener(MOUSE_OUT, [&]()->void
		{
			m_pMenuButtons[1]->setAlpha(255);
		});
	addChild(m_pMenuButtons[1], 2);

	// Exit Button
	m_pMenuButtons.push_back(new Button("../Assets/textures/ExitButton.png", "ExitButton", EXIT_BUTTON, glm::vec2(640.0f, m_pMenuButtons[1]->getTransform()->position.y + 65), true));
	m_pMenuButtons[2]->addEventListener(CLICK, [&]()-> void
		{
			m_pMenuButtons[2]->setActive(false);
			TheGame::Instance()->quit();
		});

	m_pMenuButtons[2]->addEventListener(MOUSE_OVER, [&]()->void
		{
			m_pMenuButtons[2]->setAlpha(200);
		});

	m_pMenuButtons[2]->addEventListener(MOUSE_OUT, [&]()->void
		{
			m_pMenuButtons[2]->setAlpha(255);
		});
	addChild(m_pMenuButtons[2],2);
	//END OF BUTTONS----
	
}

