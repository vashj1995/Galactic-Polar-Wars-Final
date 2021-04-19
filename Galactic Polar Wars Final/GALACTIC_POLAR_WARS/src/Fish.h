#pragma once
#ifndef __FISH__
#define __FISH__
#include "Sprite.h"


class Fish final : public Sprite {
public:
	Fish();
	~Fish();

	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

private:

	void m_checkBounds();
	void m_reset();
};
#endif