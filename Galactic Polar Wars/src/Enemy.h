#pragma once
#ifndef __ENEMY__
#define __ENEMY__

#include "EnemyAnimationState.h"
#include "Sprite.h"

class Enemy final : public Sprite
{
public:
	enum EnemyWeaponType { NONE, ICE, ALIEN };
	
	Enemy(glm::vec2 position, EnemyWeaponType weaponType);
	~Enemy();

	
	// Life Cycle Methods
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	// getters and setters
	void setDestination(glm::vec2 destination);
	void setAnimationState(EnemyAnimationState new_state);
	void setMaxSpeed(float speed);
	void setOrientation(glm::vec2 orientation);
	void setRotation(float angle);
	float getRotation() const;
	void setFacingRight(bool facingRight);

	bool hasIceBlaster();
	bool hasAlienBlaster();
	bool isFacingRight();
	
	void setIsDead();
	bool isDead() const;
	bool isDeathTimerDone() const;

private:
	void m_buildAnimations();
	void m_Move();
	glm::vec2 m_destination;
	glm::vec2 m_targetDirection;
	glm::vec2 m_orientation;
	float m_maxSpeed;
	float m_rotationAngle;
	bool m_isDead;
	bool m_facingRight;
	bool m_deathTimerDone;
	bool m_isAnimating;
	int m_animTimer;
	int m_deathTimer;
	bool m_hasIceBlaster, m_hasAlienBlaster;

	EnemyAnimationState m_currentAnimationState;
};
#endif /* defined (__ENEMY__) */