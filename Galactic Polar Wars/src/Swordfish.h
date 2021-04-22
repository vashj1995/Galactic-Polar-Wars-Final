#pragma once
#ifndef __SWORDFISH__
#define __SWORDFISH__
#include "Sprite.h"


class Swordfish final : public Sprite {
public:
	Swordfish();
	~Swordfish();

	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

private:

	void m_checkBounds();
	void m_reset();
};
#endif