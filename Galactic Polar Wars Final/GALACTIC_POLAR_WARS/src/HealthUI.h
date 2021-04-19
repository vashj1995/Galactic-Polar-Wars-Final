#pragma once
#ifndef __HEALTHUI__
#define __HEALTHUI__
#include "DisplayObject.h"

class HealthUI : public DisplayObject
{
public:
	HealthUI();
	~HealthUI();
	
	// Inherited from DisplayObject.
	void draw() override;
	void update() override;
	void clean() override;

	void setHealthPointsUI(int pts);

private:
	int m_healthPointsUI;
};

#endif
