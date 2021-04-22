#pragma once
#ifndef _FREEZER_BACKGROUND_
#define _FREEZER_BACKGROUND_
#include "DisplayObject.h"
#include "TextureManager.h"

class FreezerBackground : public DisplayObject
{
private:
	
public:
	// constructor(s)
	FreezerBackground();

	// destructor
	~FreezerBackground();

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
