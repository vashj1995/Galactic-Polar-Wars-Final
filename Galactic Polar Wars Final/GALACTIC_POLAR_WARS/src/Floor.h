#pragma once
#ifndef __FLOOR__
#define __FLOOR__

#include "DisplayObject.h"
#include "FloorType.h"

class Floor final : public DisplayObject {
public:
	Floor();
	Floor(glm::vec2 position, FloorType type);
	~Floor();
	
	// Inherited via GameObject
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	void setFloorType(FloorType type);
	FloorType getFloorType() const;

private:

	FloorType m_floorType;
	void m_checkBounds();
	void m_reset();
};


#endif 

