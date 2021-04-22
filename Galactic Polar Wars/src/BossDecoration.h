#pragma once
#ifndef _BOSS_DECORATION_
#define _BOSS_DECORATION_
#include "DisplayObject.h"
#include "TextureManager.h"

enum BossDecoType { BD_CONSOLE, BD_WINDOW };

class BossDecoration : public DisplayObject
{
private:

public:
	// constructor(s)
	BossDecoration(BossDecoType type, glm::vec2 pos);

	// destructor
	~BossDecoration();

	// life-cycle methods inherited from DisplayObject
	void draw() override;
	void update() override;
	void clean() override;

	//getters and setters
	void setDestination(glm::vec2 destination);

private:
	BossDecoType m_type;
};

#endif /* defined (__BOSS_DECORATION__) */


