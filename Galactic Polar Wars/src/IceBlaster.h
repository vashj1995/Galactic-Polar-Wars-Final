#pragma once
#ifndef __ICEBLASTER__
#define __ICEBLASTER__
#include "Sprite.h"


class IceBlaster final : public Sprite {
public:
	IceBlaster();
	~IceBlaster();

	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

private:

	void m_checkBounds();
	void m_reset();
};
#endif