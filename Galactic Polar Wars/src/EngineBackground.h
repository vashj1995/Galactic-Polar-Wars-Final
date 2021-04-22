#pragma once
#ifndef _ENGINE_BACKGROUND_
#define _ENGINE_BACKGROUND_
#include "DisplayObject.h"
#include "TextureManager.h"

class EngineBackground : public DisplayObject
{
private:

public:
	// constructor(s)
	EngineBackground();

	// destructor
	~EngineBackground();

	// life-cycle methods inherited from DisplayObject
	void draw() override;
	void update() override;
	void clean() override;

	//getters and setters
	void setDestination(glm::vec2 destination);

private:

};

#endif /* defined (__EngineBackground__) */

