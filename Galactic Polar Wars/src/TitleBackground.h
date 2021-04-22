#pragma once
#ifndef _TITLE_BACKGROUND_
#define _TITLE_BACKGROUND_
#include "DisplayObject.h"
#include "TextureManager.h"

class TitleBackground : public DisplayObject
{
private:

public:
	// constructor(s)
	TitleBackground();

	// destructor
	~TitleBackground();

	// life-cycle methods inherited from DisplayObject
	void draw() override;
	void update() override;
	void clean() override;

	//getters and setters
	void setDestination(glm::vec2 destination);

private:

	//glm::vec2 m_destination;

};

#endif /* defined (__FreezerBackground__) */
