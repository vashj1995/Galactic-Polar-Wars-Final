#pragma once
#ifndef __PLAYER__
#define __PLAYER__

#define JUMPFORCE 25.0
#define GRAV 2.0

#include "PlayerAnimationState.h"
#include "PlayerState.h"
#include "Sprite.h"

class Player final : public Sprite
{
public:
	Player();
	~Player();

	// Life Cycle Methods
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	// getters and setters
	void setDestination(glm::vec2 destination);
	void setAnimationState(PlayerAnimationState new_state);
	void setMaxSpeed(float speed);
	void setMaxVelocityY(float maxY);
	void setOrientation(glm::vec2 orientation);
	void setRotation(float angle);
	float getRotation() const;
	void setAlienBlaster(bool hasAB);
	bool getAlienBlaster() const;

	void setJumping(bool isJump);
	bool getJumping();

	void setGrounded(bool grounded);
	bool getGrounded();
	
	void stopMoving();
	void stopMovingX();
	void stopMovingY();
	void setAccelRateX(float a);
	void setAccelRateY(float a);
	double getVelocityX();
	double getVelocityY();
	void setPosX(float x);
	void setPosY(float y);

	bool canShoot();
	void setShoot(bool canShoot);

	void meleeAttack();
	
	void setFacingRight(bool facingRight);
	bool getFacingRight() const;

	void setIsDead(bool isDead);
	bool isDead();

	void getHit();

	void setHealthPoints(bool addPoint);
	int getHealthPoints() const;

	void printCoords();

private:
	void m_buildAnimations();
	void m_Move();
	glm::vec2 m_destination;
	glm::vec2 m_targetDirection;
	glm::vec2 m_orientation;
	float m_maxSpeed;
	float m_rotationAngle;
	bool m_hasAB,
		m_isJumping,
		m_isFacingRight,
		m_grounded,
		m_canShoot,
		m_isDead,
		m_isAnimating,
		m_imFrench,
		m_keyPressedRecently;
	
	float m_accelRateX,
		m_accelRateY,
		m_velocityX,
		m_maxVelocityX,
		m_velocityY,
		m_maxVelocityY,
		m_drag,
		m_gravity;

	int m_jumpTime,
		m_walkSound,
		m_healthPoints,
		m_animationTimer,
		m_keyPressTimer;

	PlayerAnimationState m_currentAnimationState;
	PlayerState m_state;
};

#endif /* defined (__PLAYER__) */