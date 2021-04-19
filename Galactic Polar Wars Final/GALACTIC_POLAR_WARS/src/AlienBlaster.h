#pragma once
#ifndef __ALIENBLASTER__
#define __ALIENBLASTER__
#include "Sprite.h"


class AlienBlaster final : public Sprite {
public:
	AlienBlaster();
	~AlienBlaster();

	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

private:

	void m_checkBounds();
	void m_reset();
};
#endif