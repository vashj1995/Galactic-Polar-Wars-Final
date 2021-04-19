#pragma once
#ifndef __PLATFORM__
#define __PLATFORM__

#include "DisplayObject.h"

class PlatformLong final : public DisplayObject {
public:
	PlatformLong();
	~PlatformLong();

	// Inherited via GameObject
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

private:

	void m_checkBounds();
	void m_reset();
};


#endif /* defined (__PLATFORM__) */
