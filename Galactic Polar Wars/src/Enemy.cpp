#include "Enemy.h"

#include "SoundManager.h"
#include "TextureManager.h"
#include "Util.h"

Enemy::Enemy(glm::vec2 position, EnemyWeaponType weaponType)
{
	setSpriteSheet(TextureManager::Instance()->getSpriteSheet("spritesheet"));
	
	// set frame width
	setWidth(41); 

	// set frame height
	setHeight(62);

	getTransform()->position = position;
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(PLAYER);
	setMaxSpeed(5.0f);
	setOrientation(glm::vec2(0.0f, -1.0f));
	setRotation(0.0f);

	m_isDead = false;
	m_deathTimerDone = false;
	m_deathTimer = 0;
	m_animTimer = 0;
	m_isAnimating = false;
	
	if(weaponType == ICE)
	{
		m_hasIceBlaster = true;
		m_hasAlienBlaster = false;
		setAnimationState(ENEMY_ICE_IDLE_RIGHT);
	}
	if(weaponType == ALIEN)
	{
		m_hasAlienBlaster = true;
		m_hasIceBlaster = false;
		setAnimationState(ENEMY_AB_IDLE_RIGHT);
	}
	if(weaponType == NONE)
	{
		m_hasIceBlaster = false;
		m_hasAlienBlaster = false;
		setAnimationState(ENEMY_IDLE_RIGHT);
	}
	
	m_buildAnimations();
}

Enemy::~Enemy()
{
	
}

void Enemy::draw()
{
	// alias for x and y
	const auto x = getTransform()->draw_position.x;
	const auto y = getTransform()->draw_position.y;

	// draw the player according to animation state
	switch (m_currentAnimationState)
	{
	case ENEMY_IDLE_LEFT:
		TextureManager::Instance()->playAnimation("spritesheet", getAnimation("e_idle"),
			x, y, 0.10f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		setFacingRight(false);
		break;
	case ENEMY_IDLE_RIGHT:
		TextureManager::Instance()->playAnimation("spritesheet", getAnimation("e_idle"),
			x, y, 0.10f, 0, 255, true);
		setFacingRight(true);
		break;
	case ENEMY_RUN_LEFT:
		TextureManager::Instance()->playAnimation("spritesheet", getAnimation("e_walk"),
			x, y, 0.35f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		setFacingRight(false);
		break;
	case ENEMY_RUN_RIGHT:
		TextureManager::Instance()->playAnimation("spritesheet", getAnimation("e_walk"),
			x, y, 0.35f, 0, 255, true);
		setFacingRight(true);
		break;
	case ENEMY_JUMP_UP_RIGHT:
		TextureManager::Instance()->playAnimation("spritesheet", getAnimation("e_jumpup"),
			x, y, 0.35f, 0, 255, true);
		break;
	case ENEMY_FALL_RIGHT:
		TextureManager::Instance()->playAnimation("spritesheet", getAnimation("e_fall"),
			x, y, 0.35f, 0, 255, true);
		setFacingRight(true);
		break;
	case ENEMY_JUMP_UP_LEFT:
		TextureManager::Instance()->playAnimation("spritesheet", getAnimation("e_jumpup"),
			x, y, 0.35f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		setFacingRight(false);
		break;
	case ENEMY_FALL_LEFT:
		TextureManager::Instance()->playAnimation("spritesheet", getAnimation("e_fall"),
			x, y, 0.35f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		setFacingRight(false);
		break;
	case ENEMY_SWIM_RIGHT:
		TextureManager::Instance()->playAnimation("spritesheet", getAnimation("e_swim"),
			x, y, 0.35f, 0, 255, true);
		setFacingRight(true);
		break;
	case ENEMY_SWIM_LEFT:
		TextureManager::Instance()->playAnimation("spritesheet", getAnimation("e_swim"),
			x, y, 0.35f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		setFacingRight(false);
		break;
	case ENEMY_DEATH_LEFT:
		TextureManager::Instance()->playAnimation("spritesheet", getAnimation("e_death"),
			x, y, 0.35f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		break;
	case ENEMY_DEATH_RIGHT:
		TextureManager::Instance()->playAnimation("spritesheet", getAnimation("e_death"),
			x, y, 0.35f, 0, 255, true);
		break;
		
	// Ice Blaster cases ----
	case ENEMY_ICE_IDLE_LEFT:
		TextureManager::Instance()->playAnimation("spritesheet", getAnimation("e_IB_idle"),
			x, y, 0.35f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		setFacingRight(false);
		break;
	case ENEMY_ICE_IDLE_RIGHT:
		TextureManager::Instance()->playAnimation("spritesheet", getAnimation("e_IB_idle"),
			x, y, 0.35f, 0, 255, true);
		setFacingRight(true);
		break;
	case ENEMY_ICE_RUN_LEFT:
		TextureManager::Instance()->playAnimation("spritesheet", getAnimation("e_IB_walk"),
			x, y, 0.35f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		setFacingRight(false);
		break;
	case ENEMY_ICE_RUN_RIGHT:
		TextureManager::Instance()->playAnimation("spritesheet", getAnimation("e_IB_walk"),
			x, y, 0.35f, 0, 255, true);
		setFacingRight(true);
		break;
		
	// Alien Blaster cases ----
	case ENEMY_AB_IDLE_LEFT:
		TextureManager::Instance()->playAnimation("spritesheet", getAnimation("e_AB_idle"),
			x, y, 0.35f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		setFacingRight(false);
		break;
	case ENEMY_AB_IDLE_RIGHT:
		TextureManager::Instance()->playAnimation("spritesheet", getAnimation("e_AB_idle"),
			x, y, 0.35f, 0, 255, true);
		setFacingRight(true);
		break;
	case ENEMY_AB_RUN_LEFT:
		TextureManager::Instance()->playAnimation("spritesheet", getAnimation("e_AB_walk"),
			x, y, 0.35f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		setFacingRight(false);
		break;
	case ENEMY_AB_RUN_RIGHT:
		TextureManager::Instance()->playAnimation("spritesheet", getAnimation("e_AB_walk"),
			x, y, 0.35f, 0, 255, true);
		setFacingRight(true);
		break;
	default:
		TextureManager::Instance()->playAnimation("spritesheet", getAnimation("e_idle"),
			x, y, 0.10f, 0, 255, true);
		break;
	}

}

void Enemy::update()
{
	if (m_isAnimating) 
	{
		m_animTimer++;
		if (m_animTimer == 30) 
		{
			m_animTimer = 0;
			m_isAnimating = true;
		}
	}

	if (m_isDead) 
	{
		m_deathTimer++;
		if (m_deathTimer == 25) 
		{
			m_deathTimer = 0;
			m_deathTimerDone = true;
		}
	}

	
	if (m_currentAnimationState == ENEMY_RUN_RIGHT)
	{
		getTransform()->position += glm::vec2(3.0f, 0.0f);
	// This if makes polars change direction, same as below
		if (getTransform()->position.x > 1200)
			setAnimationState(ENEMY_RUN_LEFT);
	}

	if (m_currentAnimationState == ENEMY_RUN_LEFT)
	{
		getTransform()->position += glm::vec2(-3.0f, 0.0f);
		if (getTransform()->position.x < 30)
			setAnimationState(ENEMY_RUN_RIGHT);
	}

	if (m_currentAnimationState == ENEMY_JUMP_UP_RIGHT || m_currentAnimationState == ENEMY_JUMP_UP_LEFT)
	{
		getTransform()->position += glm::vec2(0.0f, -5.0f);
	}

	if (m_currentAnimationState == ENEMY_FALL_RIGHT || m_currentAnimationState == ENEMY_FALL_LEFT)
	{
		getTransform()->position += glm::vec2(0.0f, 5.0f);
	}
}

void Enemy::clean()
{
}

void Enemy::setDestination(const glm::vec2 destination)
{
	m_destination = destination;
}
void Enemy::setMaxSpeed(const float speed)
{
	m_maxSpeed = speed;
}

void Enemy::setOrientation(glm::vec2 orientation)
{
	m_orientation = orientation;
}

void Enemy::setRotation(float angle)
{
	m_rotationAngle = angle;
}

float Enemy::getRotation() const
{
	return m_rotationAngle;
}

void Enemy::setFacingRight(bool facingRight)
{
	m_facingRight = facingRight;
}

bool Enemy::hasIceBlaster()
{
	return m_hasIceBlaster; ///CAUSES BUG
}

bool Enemy::hasAlienBlaster()
{
	return m_hasAlienBlaster;
}

bool Enemy::isFacingRight()
{
	return m_facingRight;
}

void Enemy::setIsDead()
{
	m_isDead = true;
	SoundManager::Instance().playSound("ADeath");
	if (m_facingRight)
		setAnimationState(ENEMY_DEATH_RIGHT);
	else
		setAnimationState(ENEMY_DEATH_LEFT);
	
}

bool Enemy::isDead() const
{
	return m_isDead;
}

bool Enemy::isDeathTimerDone() const
{
	return m_deathTimerDone;
}

void Enemy::m_Move()
{
	// magnitude
	m_targetDirection = m_destination - getTransform()->position;

	// normalized direction
	m_targetDirection = Util::normalize(m_targetDirection);

	getRigidBody()->velocity = m_targetDirection * m_maxSpeed;

	getTransform()->position += getRigidBody()->velocity;
}

void Enemy::setAnimationState(const EnemyAnimationState new_state)
{
	m_currentAnimationState = new_state;
}

void Enemy::m_buildAnimations()
{

	// ------------------------------------------------- WALK ------------------------
	Animation walkAnimation = Animation();

	walkAnimation.name = "e_walk";
	walkAnimation.frames.push_back(getSpriteSheet()->getFrame("polar-idle"));
	walkAnimation.frames.push_back(getSpriteSheet()->getFrame("polar-walk-1"));
	walkAnimation.frames.push_back(getSpriteSheet()->getFrame("polar-walk-2"));
	walkAnimation.frames.push_back(getSpriteSheet()->getFrame("polar-walk-3"));
	walkAnimation.frames.push_back(getSpriteSheet()->getFrame("polar-walk-4"));
	walkAnimation.frames.push_back(getSpriteSheet()->getFrame("polar-walk-5"));
	walkAnimation.frames.push_back(getSpriteSheet()->getFrame("polar-walk-6"));

	setAnimation(walkAnimation);
	
	// ------------------------------------------------- IDLE ------------------------
	Animation idleAnimation = Animation();

	idleAnimation.name = "e_idle";
	idleAnimation.frames.push_back(getSpriteSheet()->getFrame("polar-idle"));

	setAnimation(idleAnimation);
	
	// --------------------------------------------- ICE BLASTER WALK ------------------------
	Animation walkAnimationIB = Animation();

	walkAnimationIB.name = "e_IB_walk";
	walkAnimationIB.frames.push_back(getSpriteSheet()->getFrame("polar-IB-idle"));
	walkAnimationIB.frames.push_back(getSpriteSheet()->getFrame("polar-IB-walk-1"));
	walkAnimationIB.frames.push_back(getSpriteSheet()->getFrame("polar-IB-walk-2"));
	walkAnimationIB.frames.push_back(getSpriteSheet()->getFrame("polar-IB-walk-3"));
	walkAnimationIB.frames.push_back(getSpriteSheet()->getFrame("polar-IB-walk-4"));
	walkAnimationIB.frames.push_back(getSpriteSheet()->getFrame("polar-IB-walk-5"));
	walkAnimationIB.frames.push_back(getSpriteSheet()->getFrame("polar-IB-walk-6"));

	setAnimation(walkAnimationIB);
	
	// --------------------------------------------- ICE BLASTER IDLE ------------------------
	Animation idleAnimationIB = Animation();

	idleAnimationIB.name = "e_IB_idle";
	idleAnimationIB.frames.push_back(getSpriteSheet()->getFrame("polar-IB-idle"));

	setAnimation(idleAnimationIB);
	
	// --------------------------------------------- ALIEN BLASTER WALK ------------------------
	Animation walkAnimationAB = Animation();

	walkAnimationAB.name = "e_AB_walk";
	walkAnimationAB.frames.push_back(getSpriteSheet()->getFrame("polar-AB-idle"));
	walkAnimationAB.frames.push_back(getSpriteSheet()->getFrame("polar-AB-walk-1"));
	walkAnimationAB.frames.push_back(getSpriteSheet()->getFrame("polar-AB-walk-2"));
	walkAnimationAB.frames.push_back(getSpriteSheet()->getFrame("polar-AB-walk-3"));
	walkAnimationAB.frames.push_back(getSpriteSheet()->getFrame("polar-AB-walk-4"));
	walkAnimationAB.frames.push_back(getSpriteSheet()->getFrame("polar-AB-walk-5"));
	walkAnimationAB.frames.push_back(getSpriteSheet()->getFrame("polar-AB-walk-6"));

	setAnimation(walkAnimationAB);
	
	// --------------------------------------------- ALIEN BLASTER IDLE ------------------------
	Animation idleAnimationAB = Animation();

	idleAnimationAB.name = "e_AB_idle";
	idleAnimationAB.frames.push_back(getSpriteSheet()->getFrame("polar-AB-idle"));

	setAnimation(idleAnimationAB);
	
	// ------------------------------------------------- JUMP ------------------------ - - - doesn't exist yet fyi
	Animation jumpUpAnimation = Animation();

	jumpUpAnimation.name = "e_jumpup";
	jumpUpAnimation.frames.push_back(getSpriteSheet()->getFrame("polar-jump"));

	setAnimation(jumpUpAnimation);

	// ------------------------------------------------- FALL ------------------------ - - - doesn't exist yet fyi
	Animation fallAnimation = Animation();

	fallAnimation.name = "e_fall";
	fallAnimation.frames.push_back(getSpriteSheet()->getFrame("polar-fall"));

	setAnimation(fallAnimation);

	// ------------------------------------------------- SWIM ----------------------- - - - doesn't exist yet fyi
	Animation swimAnimation = Animation();

	swimAnimation.name = "e_swim";
	swimAnimation.frames.push_back(getSpriteSheet()->getFrame("polar-swim-4"));
	swimAnimation.frames.push_back(getSpriteSheet()->getFrame("polar-swim-3"));
	swimAnimation.frames.push_back(getSpriteSheet()->getFrame("polar-swim-2"));
	swimAnimation.frames.push_back(getSpriteSheet()->getFrame("polar-swim-1"));
	swimAnimation.frames.push_back(getSpriteSheet()->getFrame("polar-swim-2"));
	swimAnimation.frames.push_back(getSpriteSheet()->getFrame("polar-swim-3"));

	setAnimation(swimAnimation);

	// ------------------------------------------------- DEATH -----------------------
	Animation deathAnimation = Animation();

	deathAnimation.name = "e_death";
	deathAnimation.frames.push_back(getSpriteSheet()->getFrame("polar-death-1"));
	deathAnimation.frames.push_back(getSpriteSheet()->getFrame("polar-death-2"));
	deathAnimation.frames.push_back(getSpriteSheet()->getFrame("polar-death-3"));
	deathAnimation.frames.push_back(getSpriteSheet()->getFrame("polar-death-4"));
	deathAnimation.frames.push_back(getSpriteSheet()->getFrame("polar-death-5"));

	setAnimation(deathAnimation);
}
