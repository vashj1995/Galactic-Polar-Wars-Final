#pragma once
#ifndef __PAUSE_SCENE__
#define __PAUSE_SCENE__

#include "Scene.h"
#include "Label.h"
#include "Button.h"
#include "TitleBackground.h"
#include "SoundManager.h"

#include <vector>

class PauseScene final : public Scene
{
public:
	PauseScene();
	~PauseScene();

	// Inherited via Scene
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;

private:

	TitleBackground* m_pPauseBackground;

	std::vector<Button*> m_pPauseButtons;
};

#endif /* defined (__PAUSE_SCENE__) */