#pragma once
#ifndef __GREGORY_HEALTH_BAR__
#define __GREGORY_HEALTH_BAR__
#include "DisplayObject.h"

class GregoryHealthBar : public DisplayObject
{
public:
	GregoryHealthBar();
	~GregoryHealthBar();

	// Inherited from DisplayObject.
	void draw() override;
	void update() override;
	void clean() override;

	void setHealthPointsUI(int pts);

private:
	int m_gregoryHealth;
};

#endif/*(__GREGORY_HEALTH_BAR__)*/

