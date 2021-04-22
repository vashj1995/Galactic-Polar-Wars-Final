#pragma once
#ifndef __START_SCENE__
#define __START_SCENE__

#include "Scene.h"
#include "Label.h"
#include "Button.h"
#include "TitleBackground.h"
#include "SoundManager.h"

#include <vector>

class StartScene final : public Scene
{
public:
	StartScene();
	~StartScene();

	// Inherited via Scene
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;
	
private:

	TitleBackground* m_pTitleBackground;

	std::vector<Button*> m_pMenuButtons;
};

#endif /* defined (__START_SCENE__) */