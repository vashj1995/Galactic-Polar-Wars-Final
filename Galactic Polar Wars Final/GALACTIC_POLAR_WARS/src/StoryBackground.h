#pragma once
#ifndef _STORY_BACKGROUND_
#define _STORY_BACKGROUND_
#include "DisplayObject.h"
#include "TextureManager.h"

class StoryBackground : public DisplayObject
{
private:

public:
	// constructor(s)
	StoryBackground();

	// destructor
	~StoryBackground();

	// life-cycle methods inherited from DisplayObject
	void draw() override;
	void update() override;
	void clean() override;

	//getters and setters
	void setDestination(glm::vec2 destination);

private:

	//glm::vec2 m_destination;

};

#endif /* defined (__StoryBackground__) */

