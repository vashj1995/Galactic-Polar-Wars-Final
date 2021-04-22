#pragma once
#ifndef __STORY_SCENE__
#define __STORY_SCENE__

#include "Scene.h"
#include "Label.h"
#include "Button.h"
#include "StoryBackground.h"
#include "SoundManager.h"

#include <vector>

class StoryScene final : public Scene
{
public:
	StoryScene();
	~StoryScene();

	// Inherited via Scene
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;

private:

	StoryBackground* m_pStoryBackground;

	std::vector<Button*> m_pStoryButtons;
};

#endif /* defined (__STORY_SCENE__) */
