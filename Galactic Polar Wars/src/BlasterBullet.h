#pragma once
#ifndef __BLASTER_BULLET__
#define __BLASTER_BULLET__
#include "DisplayObject.h"
#include "TextureManager.h"

class BlasterBullet final : public DisplayObject
{
public:
	enum BulletType { ALIEN, ICE };
	
	BlasterBullet();
	BlasterBullet(glm::vec2 position, bool direction, BulletType type);
	~BlasterBullet();

	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	void setDestination(glm::vec2 destination);
	void setMaxSpeed(float speed);
	void setOrientation(glm::vec2 orientation);
	void setAccelerationRate(float rate);

	glm::vec2 getOrientation() const;
	float getAccelerationRate() const;


	void m_checkBounds();
	void m_reset();
private:
	glm::vec2 m_destination;
	glm::vec2 m_orientation;
	float m_maxSpeed;
	float m_accelerationRate;
	bool m_direction;

	BulletType m_type;

	void m_Move();

};
#endif /* defined (__BLASTER_BULLET__) */