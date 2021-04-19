#pragma once
#ifndef __AMMO__
#define __AMMO__
#include "Sprite.h"


class Ammo final : public Sprite {
public:
	Ammo();
	~Ammo();

	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

private:

	void m_checkBounds();
	void m_reset();
};
#endif