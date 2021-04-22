#include "Gregory.h"

#include "SoundManager.h"
#include "TextureManager.h"
#include "Util.h"

Gregory::Gregory(glm::vec2 position)
{
	TextureManager::Instance()->loadSpriteSheet(
		"../Assets/sprites/GregorySheet.txt",
		"../Assets/sprites/GregorySheet.png",
		"gSpritesheet");

	setSpriteSheet(TextureManager::Instance()->getSpriteSheet("gSpritesheet"));

	// set frame width
	setWidth(161);

	// set frame height
	setHeight(150);

	getTransform()->position = position;
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(PLAYER);
	setMaxSpeed(5.0f);
	setOrientation(glm::vec2(0.0f, -1.0f));
	setRotation(0.0f);

	m_isAngry = false;

	m_healthPoints = 17;
	m_walkSound = 0;
	m_growlTimer = 0;

	SoundManager::Instance().load("../Assets/audio/Gregory_Footsteps.wav", "GStep", SOUND_SFX);
	SoundManager::Instance().load("../Assets/audio/Gregory_Growl.wav", "GGrowl", SOUND_SFX);

	m_buildAnimations();
}

Gregory::~Gregory()
= default;

void Gregory::draw()
{
	// alias for x and y
	const auto x = getTransform()->draw_position.x;
	const auto y = getTransform()->draw_position.y;

	// draw the player according to animation state
	switch (m_currentAnimationState)
	{
	case GREGORY_IDLE_LEFT:
		TextureManager::Instance()->playAnimation("gSpritesheet", getAnimation("g_idle"),
			x, y, 0.10f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		setFacingRight(false);
		break;
	case GREGORY_IDLE_RIGHT:
		TextureManager::Instance()->playAnimation("gSpritesheet", getAnimation("g_idle"),
			x, y, 0.10f, 0, 255, true);
		setFacingRight(true);
		break;
	case GREGORY_RUN_LEFT:
		TextureManager::Instance()->playAnimation("gSpritesheet", getAnimation("g_walk"),
			x, y, 0.35f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		setFacingRight(false);
		break;
	case GREGORY_RUN_RIGHT:
		TextureManager::Instance()->playAnimation("gSpritesheet", getAnimation("g_walk"),
			x, y, 0.35f, 0, 255, true);
		setFacingRight(true);
		break;
	case GREGORY_DEATH_LEFT:
		TextureManager::Instance()->playAnimation("gSpritesheet", getAnimation("g_death"),
			x, y, 0.35f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		break;
	case GREGORY_DEATH_RIGHT:
		TextureManager::Instance()->playAnimation("gSpritesheet", getAnimation("g_death"),
			x, y, 0.35f, 0, 255, true);
		break;
	case GREGORY_HIT_LEFT:
		TextureManager::Instance()->playAnimation("gSpritesheet", getAnimation("g_get_hit"),
			x, y, 0.35f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		break;
	case GREGORY_HIT_RIGHT:
		TextureManager::Instance()->playAnimation("gSpritesheet", getAnimation("g_get_hit"),
			x, y, 0.35f, 0, 255, true);
		break;
	default:
		TextureManager::Instance()->playAnimation("gSpritesheet", getAnimation("g_idle"),
			x, y, 0.10f, 0, 255, true);
		break;
	}

}

void Gregory::update()
{
	//for Growl sfx
	m_growlTimer++;

	if (m_growlTimer >= 360)
	{
		SoundManager::Instance().playSound("GGrowl");

		m_growlTimer = 0;
	}


	if(m_isAnimating)
	{
		m_animTimer++;
		if(m_animTimer == 40)
		{
			m_animTimer = 0;
			m_isAnimating = false;
			if (m_facingRight)
				setAnimationState(GREGORY_IDLE_RIGHT);
			else
				setAnimationState(GREGORY_IDLE_LEFT);
		}
	}
	
	if (m_isDead)
	{
		m_deathTimer++;
		if (m_deathTimer >= 20)
		{
			m_deathTimer = 0;
			m_deathTimerDone = true;
		}
	}


	if (m_currentAnimationState == GREGORY_RUN_RIGHT && !m_isAnimating)
	{
		if (!m_isAngry)
			getTransform()->position += glm::vec2(1.5f, 0.0f);
		else if (m_isAngry)
			getTransform()->position += glm::vec2(2.7f, 0.0f);
		// This if makes polars change direction, same as below
	}

	if (m_currentAnimationState == GREGORY_RUN_LEFT && !m_isAnimating)
	{
		if (!m_isAngry)
			getTransform()->position += glm::vec2(-1.5f, 0.0f);
		else if (m_isAngry)
			getTransform()->position += glm::vec2(-2.7f, 0.0f);
	}
}

void Gregory::clean()
{
}

void Gregory::setDestination(const glm::vec2 destination)
{
	m_destination = destination;
}
void Gregory::setMaxSpeed(const float speed)
{
	m_maxSpeed = speed;
}

void Gregory::setOrientation(glm::vec2 orientation)
{
	m_orientation = orientation;
}

void Gregory::setRotation(float angle)
{
	m_rotationAngle = angle;
}

float Gregory::getRotation() const
{
	return m_rotationAngle;
}

void Gregory::setFacingRight(bool facingRight)
{
	m_facingRight = facingRight;
}

bool Gregory::isFacingRight()
{
	return m_facingRight;
}


bool Gregory::isDeathTimerDone() const
{
	return m_deathTimerDone;
}

bool Gregory::getIsAnimating()
{
	return m_isAnimating;
}

void Gregory::flipAngry()
{
	m_isAngry = !m_isAngry;
}

void Gregory::setIsDead()
{
	m_isDead = true;
	if (m_facingRight)
		setAnimationState(GREGORY_DEATH_RIGHT);
	else
		setAnimationState(GREGORY_DEATH_LEFT);
	SoundManager::Instance().playSound("ADeath");
}

bool Gregory::isDead() const
{
	return m_isDead;
}

void Gregory::getHit()
{
	//if (!m_isAngry)
		m_isAnimating = true;
	if (m_facingRight)
		setAnimationState(GREGORY_HIT_RIGHT);
	else
		setAnimationState(GREGORY_HIT_LEFT);
}

void Gregory::setHealthPoints(bool addPoint)
{
	if (addPoint && m_healthPoints <= 17)
		m_healthPoints += 1;
	else if (!addPoint && m_healthPoints > 0)
		m_healthPoints -= 1;
}

int Gregory::getHealthPoints() const
{
	return m_healthPoints;
}

void Gregory::moveToTarget(Player* player)
{
	if(Util::distance(getTransform()->position, player->getTransform()->position) > 500.0f && (getTransform()->position.x > 530.0f && getTransform()->position.x < 1840.0f))
     {
		if(player->getTransform()->position.x < getTransform()->position.x && 
			Util::distance(getTransform()->position, player->getTransform()->position) > 50.0f)// && !m_isAnimating)
		{
			m_walkSound++;

			if (m_walkSound > 45)
			{
				SoundManager::Instance().playSound("GStep");
				m_walkSound = 0;
			}

			setFacingRight(false);
			setAnimationState(GREGORY_RUN_LEFT);
		}
		else if(player->getTransform()->position.x > getTransform()->position.x && 
			Util::distance(getTransform()->position, player->getTransform()->position) > 50.0f )//&& !m_isAnimating)
		{
			m_walkSound++;

			if (m_walkSound > 45)
			{
				SoundManager::Instance().playSound("GStep");
				m_walkSound = 0;
			}
			setFacingRight(true);
			setAnimationState(GREGORY_RUN_RIGHT);
		}
	}
}

void Gregory::m_Move()
{
	// magnitude
	m_targetDirection = m_destination - getTransform()->position;

	// normalized direction
	m_targetDirection = Util::normalize(m_targetDirection);

	getRigidBody()->velocity = m_targetDirection * m_maxSpeed;

	getTransform()->position += getRigidBody()->velocity;
}

void Gregory::setAnimationState(const GregoryAnimationState new_state)
{
	m_currentAnimationState = new_state;
}

void Gregory::m_buildAnimations()
{

	// ------------------------------------------------- WALK ------------------------
	Animation gWalkAnimation = Animation();

	gWalkAnimation.name = "g_walk";
	gWalkAnimation.frames.push_back(getSpriteSheet()->getFrame("gregory-idle"));
	gWalkAnimation.frames.push_back(getSpriteSheet()->getFrame("gregory-walk-1"));
	gWalkAnimation.frames.push_back(getSpriteSheet()->getFrame("gregory-walk-2"));
	gWalkAnimation.frames.push_back(getSpriteSheet()->getFrame("gregory-walk-3"));
	gWalkAnimation.frames.push_back(getSpriteSheet()->getFrame("gregory-walk-4"));
	gWalkAnimation.frames.push_back(getSpriteSheet()->getFrame("gregory-walk-5"));

	setAnimation(gWalkAnimation);

	// ------------------------------------------------- IDLE ------------------------
	Animation gIdleAnimation = Animation();

	gIdleAnimation.name = "g_idle";
	gIdleAnimation.frames.push_back(getSpriteSheet()->getFrame("gregory-idle"));

	setAnimation(gIdleAnimation);

	// ------------------------------------------------- GET HIT ---------------------
	Animation gGetHitAnimation = Animation();

	gGetHitAnimation.name = "g_get_hit";
	gGetHitAnimation.frames.push_back(getSpriteSheet()->getFrame("gregory-hit-1"));
	gGetHitAnimation.frames.push_back(getSpriteSheet()->getFrame("gregory-hit-2"));
	gGetHitAnimation.frames.push_back(getSpriteSheet()->getFrame("gregory-hit-3"));
	gGetHitAnimation.frames.push_back(getSpriteSheet()->getFrame("gregory-hit-4"));

	setAnimation(gGetHitAnimation);

	// ------------------------------------------------- DEATH -----------------------
	Animation gDeathAnimation = Animation();

	gDeathAnimation.name = "g_death";
	gDeathAnimation.frames.push_back(getSpriteSheet()->getFrame("gregory-die-1"));
	gDeathAnimation.frames.push_back(getSpriteSheet()->getFrame("gregory-die-2"));
	gDeathAnimation.frames.push_back(getSpriteSheet()->getFrame("gregory-die-3"));
	gDeathAnimation.frames.push_back(getSpriteSheet()->getFrame("gregory-die-4"));

	setAnimation(gDeathAnimation);
}
