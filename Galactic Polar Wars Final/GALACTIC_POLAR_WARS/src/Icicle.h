#pragma once
#ifndef __ICICLE__
#define __ICICLE__
#include "Sprite.h"


class Icicle final : public Sprite {
public:
	Icicle();
	~Icicle();

	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

private:

	void m_checkBounds();
	void m_reset();
};
#endif