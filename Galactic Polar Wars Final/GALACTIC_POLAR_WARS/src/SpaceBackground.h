#pragma once
#ifndef _SPACE_BACKGROUND_
#define _SPACE_BACKGROUND_
#include "DisplayObject.h"
#include "TextureManager.h"

enum SpaceBkgType { SPACE_REG, SPACE_WIN, SPACE_LOSE };

class SpaceBackground : public DisplayObject
{
private:

public:
	// constructor(s)
	SpaceBackground();
	SpaceBackground(SpaceBkgType type);

	// destructor
	~SpaceBackground();

	// life-cycle methods inherited from DisplayObject
	void draw() override;
	void update() override;
	void clean() override;

	//getters and setters
	void setDestination(glm::vec2 destination);

private:
	SpaceBkgType m_spaceBkgType;
	//glm::vec2 m_destination;

};

#endif /* defined (__FreezerBackground__) */
