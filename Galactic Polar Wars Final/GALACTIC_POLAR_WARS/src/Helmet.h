#pragma once
#ifndef __HELMET__
#define __HELMET__
#include "Sprite.h"


class Helmet final : public Sprite {
public:
	Helmet();
	~Helmet();

	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

private:

	void m_checkBounds();
	void m_reset();
};
#endif