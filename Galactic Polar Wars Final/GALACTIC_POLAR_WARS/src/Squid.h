#pragma once
#ifndef __SQUID__
#define __SQUID__
#include "Sprite.h"


class Squid final : public Sprite {
public:
	Squid();
	~Squid();

	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

private:

	void m_checkBounds();
	void m_reset();
};
#endif