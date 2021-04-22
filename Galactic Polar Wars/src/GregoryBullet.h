#pragma once
#ifndef __GREGORY_BULLET__
#define __GREGORY_BULLET__
#include "DisplayObject.h"
#include "TextureManager.h"

enum TYPE {HORIZONTAL, DIAGONAL_UP, DIAGONAL_DOWN};

class GregoryBullet final : public DisplayObject
{
public:

	GregoryBullet();
	GregoryBullet(glm::vec2 position, bool direction, TYPE type);
	~GregoryBullet();

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

	void m_Move();

	TYPE m_type;
};
#endif /* defined (__GREGORY_BULLET__) */
