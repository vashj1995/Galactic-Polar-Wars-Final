#pragma once
#ifndef __KEYCARD__
#define __KEYCARD__
#include "Sprite.h"


class Keycard final : public Sprite {
public:
	Keycard();
	~Keycard();

	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

private:

	void m_checkBounds();
	void m_reset();
};
#endif