#pragma once
#ifndef __MENU_BACKGROUND__
#define __MENU_BACKGROUND__
#include "DisplayObject.h"
#include "TextureManager.h"

class MenuBackground
{
private:

public: 
	MenuBackground();

	~MenuBackground();

	void draw() override;
	void update() override;
	void clean() override;

	void setDestination(glm::vec2 destination);

};

#endif /* defined (__MenuBackground__) */


