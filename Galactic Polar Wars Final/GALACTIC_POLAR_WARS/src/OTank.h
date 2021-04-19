#pragma once
#ifndef __OTANK__
#define __OTANK__
#include "Sprite.h"


class OTank final : public Sprite {
public:
	OTank();
	~OTank();

	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

private:

	void m_checkBounds();
	void m_reset();
};
#endif