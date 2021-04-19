#pragma once
#ifndef __GREGORY__
#define __GREGORY__

#include "GregoryAnimationState.h"
#include "Player.h"
#include "Sprite.h"

class Gregory final : public Sprite
{
public:
	Gregory(glm::vec2 position);
	~Gregory();

	// Life Cycle Methods
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	// getters and setters
	void setDestination(glm::vec2 destination);
	void setAnimationState(GregoryAnimationState new_state);
	void setMaxSpeed(float speed);
	void setOrientation(glm::vec2 orientation);
	void setRotation(float angle);
	float getRotation() const;
	void setFacingRight(bool facingRight);

	bool isFacingRight();

	void setIsDead();
	bool isDead() const;
	bool isDeathTimerDone() const;

	bool getIsAnimating();

	void flipAngry();
	
	void getHit();
	
	void setHealthPoints(bool addPoint);
	int getHealthPoints() const;

	void moveToTarget(Player* player_position);

private:
	void m_buildAnimations();
	void m_Move();

	glm::vec2 m_destination;
	glm::vec2 m_targetDirection;
	glm::vec2 m_orientation;

	float m_maxSpeed,
		m_rotationAngle;

	bool m_isDead,
		m_facingRight;
	int m_deathTimer = 0;
	bool m_deathTimerDone = false;
	bool m_isAnimating;
	int m_animTimer;
	
	int m_healthPoints,
		m_walkSound,
		m_growlTimer;

	bool m_isAngry;

	GregoryAnimationState m_currentAnimationState;
};
#endif /* defined (__GREGORY__) */
