#include "Player.h"


#include "CollisionManager.h"
#include "EventManager.h"
#include "SoundManager.h"
#include "TextureManager.h"
#include "Util.h"
#include <iostream>

Player::Player(): m_currentAnimationState(PLAYER_IDLE_RIGHT)
{
	setSpriteSheet(TextureManager::Instance()->getSpriteSheet("spritesheet"));
	
	// set frame width
	setWidth(41); 

	// set frame height
	setHeight(62); 

	getTransform()->position = glm::vec2(400.0f, 500.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(PLAYER);
	setMaxSpeed(10.0f);
	setOrientation(glm::vec2(0.0f, -1.0f));
	setRotation(0.0f);
	setJumping(false);

	// Variables for platforming.
	m_drag = 0.8f;
	m_gravity = GRAV;
	m_grounded = true;
	m_velocityX = 0;
	m_velocityY = 0;
	m_accelRateX = 0;
	m_accelRateY = 0;
	m_maxVelocityX = 10.0f;
	m_maxVelocityY = JUMPFORCE;
	m_state = STATE_FALL;

	m_healthPoints = 5;
	m_walkSound = 0;
	
	SoundManager::Instance().load("../assets/audio/Jump.wav", "jump", SOUND_SFX);
	SoundManager::Instance().load("../assets/audio/Walk_lng.wav", "walk", SOUND_SFX);
	SoundManager::Instance().setSoundVolume(20);

	m_buildAnimations();
}

Player::~Player()
= default;

void Player::draw()
{
	// alias for x and y
	const auto x = getTransform()->draw_position.x;
	const auto y = getTransform()->draw_position.y;

	// draw the player according to animation state
	switch(m_currentAnimationState)
	{
		// ---------------------------------------------------------------------------------
	case PLAYER_IDLE_LEFT:
		if(m_imFrench)
			TextureManager::Instance()->playAnimation("spritesheet", getAnimation("p_french_idle"),
				x, y, 0.10f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		else
			TextureManager::Instance()->playAnimation("spritesheet", getAnimation("p_ice_idle"),
				x, y, 0.10f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		break;
	case PLAYER_IDLE_RIGHT:
		if (m_imFrench)
			TextureManager::Instance()->playAnimation("spritesheet", getAnimation("p_french_idle"),
				x, y, 0.10f, 0, 255, true);
		else
			TextureManager::Instance()->playAnimation("spritesheet", getAnimation("p_ice_idle"),
			x, y, 0.10f, 0, 255, true);
		break;
	case PLAYER_RUN_LEFT:
		if (m_imFrench)
			TextureManager::Instance()->playAnimation("spritesheet", getAnimation("p_french_walk"),
				x, y, 0.35f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		else
			TextureManager::Instance()->playAnimation("spritesheet", getAnimation("p_ice_walk"),
			x, y, 0.35f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		break;
	case PLAYER_RUN_RIGHT:
		if (m_imFrench)
			TextureManager::Instance()->playAnimation("spritesheet", getAnimation("p_french_walk"),
				x, y, 0.35f, 0, 255, true);
		else
			TextureManager::Instance()->playAnimation("spritesheet", getAnimation("p_ice_walk"),
			x, y, 0.35f, 0, 255, true);
		break;
	case PLAYER_JUMP_UP_RIGHT:
		if (m_imFrench)
			TextureManager::Instance()->playAnimation("spritesheet", getAnimation("p_french_jump"),
				x, y, 0.35f, 0, 255, true);
		else
			TextureManager::Instance()->playAnimation("spritesheet", getAnimation("p_ice_jump"),
			x, y, 0.35f, 0, 255, true);
		break;
	case PLAYER_FALL_RIGHT:
		if (m_imFrench)
			TextureManager::Instance()->playAnimation("spritesheet", getAnimation("p_french_fall"),
				x, y, 0.35f, 0, 255, true);
		else
			TextureManager::Instance()->playAnimation("spritesheet", getAnimation("p_ice_fall"),
			x, y, 0.35f, 0, 255, true);
		break;
	case PLAYER_JUMP_UP_LEFT:
		if (m_imFrench)
			TextureManager::Instance()->playAnimation("spritesheet", getAnimation("p_french_jump"),
				x, y, 0.35f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		else
			TextureManager::Instance()->playAnimation("spritesheet", getAnimation("p_ice_jump"),
			x, y, 0.35f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		break;
	case PLAYER_FALL_LEFT:
		if (m_imFrench)
			TextureManager::Instance()->playAnimation("spritesheet", getAnimation("p_french_fall"),
				x, y, 0.35f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		else
			TextureManager::Instance()->playAnimation("spritesheet", getAnimation("p_ice_fall"),
			x, y, 0.35f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		break;
	case PLAYER_SWIM_RIGHT:
		TextureManager::Instance()->playAnimation("spritesheet", getAnimation("p_swim"),
			x, y, 0.35f, 0, 255, true);
		break;
	case PLAYER_SWIM_LEFT:
		TextureManager::Instance()->playAnimation("spritesheet", getAnimation("p_swim"),
			x, y, 0.35f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		break;
	case PLAYER_DEATH_LEFT:
		if (m_imFrench)
			TextureManager::Instance()->playAnimation("spritesheet", getAnimation("p_french_death"),
				x, y, 0.35f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		else
			TextureManager::Instance()->playAnimation("spritesheet", getAnimation("p_death"),
			x, y, 0.35f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		break;
	case PLAYER_DEATH_RIGHT:
		if (m_imFrench)
			TextureManager::Instance()->playAnimation("spritesheet", getAnimation("p_french_death"),
				x, y, 0.35f, 0, 255, true);
		else
			TextureManager::Instance()->playAnimation("spritesheet", getAnimation("p_death"),
			x, y, 0.35f, 0, 255, true);
		break;
	case PLAYER_HURT_LEFT:
		if (m_imFrench)
			TextureManager::Instance()->playAnimation("spritesheet", getAnimation("p_french_hurt"),
				x, y, 0.35f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		else
			TextureManager::Instance()->playAnimation("spritesheet", getAnimation("p_hurt"),
			x, y, 0.35f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		break;
	case PLAYER_HURT_RIGHT:
		if (m_imFrench)
			TextureManager::Instance()->playAnimation("spritesheet", getAnimation("p_french_hurt"),
				x, y, 0.35f, 0, 255, true);
		else
			TextureManager::Instance()->playAnimation("spritesheet", getAnimation("p_hurt"),
			x, y, 0.35f, 0, 255, true);
		break;
		// ---------------------------------------------------------------------------------
	case PLAYER_AB_IDLE_LEFT:
		if (m_imFrench)
			TextureManager::Instance()->playAnimation("spritesheet", getAnimation("p_french_idle_AB"),
				x, y, 0.10f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		else
			TextureManager::Instance()->playAnimation("spritesheet", getAnimation("p_ab_idle"),
			x, y, 0.10f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		break;
	case PLAYER_AB_IDLE_RIGHT:
		if (m_imFrench)
			TextureManager::Instance()->playAnimation("spritesheet", getAnimation("p_french_idle_AB"),
				x, y, 0.10f, 0, 255, true);
		else
			TextureManager::Instance()->playAnimation("spritesheet", getAnimation("p_ab_idle"),
			x, y, 0.10f, 0, 255, true);
		break;
	case PLAYER_AB_RUN_LEFT:
		if (m_imFrench)
			TextureManager::Instance()->playAnimation("spritesheet", getAnimation("p_french_walk_AB"),
				x, y, 0.35f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		else
			TextureManager::Instance()->playAnimation("spritesheet", getAnimation("p_ab_walk"),
			x, y, 0.35f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		break;
	case PLAYER_AB_RUN_RIGHT:
		if (m_imFrench)
			TextureManager::Instance()->playAnimation("spritesheet", getAnimation("p_french_walk_AB"),
				x, y, 0.35f, 0, 255, true);
		else
			TextureManager::Instance()->playAnimation("spritesheet", getAnimation("p_ab_walk"),
			x, y, 0.35f, 0, 255, true);
		break;
	case PLAYER_AB_JUMP_UP_RIGHT:
		if (m_imFrench)
			TextureManager::Instance()->playAnimation("spritesheet", getAnimation("p_french_jump_AB"),
				x, y, 0.35f, 0, 255, true);
		else
			TextureManager::Instance()->playAnimation("spritesheet", getAnimation("p_ab_jump"),
			x, y, 0.35f, 0, 255, true);
		break;
	case PLAYER_AB_FALL_RIGHT:
		if (m_imFrench)
			TextureManager::Instance()->playAnimation("spritesheet", getAnimation("p_french_fall_AB"),
				x, y, 0.35f, 0, 255, true);
		else
			TextureManager::Instance()->playAnimation("spritesheet", getAnimation("p_ab_fall"),
			x, y, 0.35f, 0, 255, true);
		break;
	case PLAYER_AB_JUMP_UP_LEFT:
		if (m_imFrench)
			TextureManager::Instance()->playAnimation("spritesheet", getAnimation("p_french_jump_AB"),
				x, y, 0.35f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		else
			TextureManager::Instance()->playAnimation("spritesheet", getAnimation("p_ab_jump"),
			x, y, 0.35f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		break;
	case PLAYER_AB_FALL_LEFT:
		if (m_imFrench)
			TextureManager::Instance()->playAnimation("spritesheet", getAnimation("p_french_fall_AB"),
				x, y, 0.35f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		else
			TextureManager::Instance()->playAnimation("spritesheet", getAnimation("p_ab_fall"),
			x, y, 0.35f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		break;
	case PLAYER_AB_SWIM_RIGHT:
		TextureManager::Instance()->playAnimation("spritesheet", getAnimation("p_ab_swim"),
			x, y, 0.35f, 0, 255, true);
		break;
	case PLAYER_AB_SWIM_LEFT:
		TextureManager::Instance()->playAnimation("spritesheet", getAnimation("p_ab_swim"),
			x, y, 0.35f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		break;
		// ---------------------------------------------------------------------------------
	case PLAYER_ICE_IDLE_LEFT:
		if (m_imFrench)
			TextureManager::Instance()->playAnimation("spritesheet", getAnimation("p_french_idle"),
				x, y, 0.35f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		else
			TextureManager::Instance()->playAnimation("spritesheet", getAnimation("p_ice_idle"),
			x, y, 0.35f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		break;
	case PLAYER_ICE_IDLE_RIGHT:
		if (m_imFrench)
			TextureManager::Instance()->playAnimation("spritesheet", getAnimation("p_french_idle"),
				x, y, 0.35f, 0, 255, true);
		else
			TextureManager::Instance()->playAnimation("spritesheet", getAnimation("p_ice_idle"),
			x, y, 0.35f, 0, 255, true);
		break;
	case PLAYER_ICE_WALK_LEFT:
		if (m_imFrench)
			TextureManager::Instance()->playAnimation("spritesheet", getAnimation("p_french_walk"),
				x, y, 0.35f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		else
			TextureManager::Instance()->playAnimation("spritesheet", getAnimation("p_ice_walk"),
			x, y, 0.35f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		break;
	case PLAYER_ICE_WALK_RIGHT:
		if (m_imFrench)
			TextureManager::Instance()->playAnimation("spritesheet", getAnimation("p_french_walk"),
				x, y, 0.35f, 0, 255, true);
		else
			TextureManager::Instance()->playAnimation("spritesheet", getAnimation("p_ice_walk"),
			x, y, 0.35f, 0, 255, true);
		break;
	case PLAYER_ICE_JUMP_LEFT:
		if (m_imFrench)
			TextureManager::Instance()->playAnimation("spritesheet", getAnimation("p_french_jump"),
				x, y, 0.35f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		else
			TextureManager::Instance()->playAnimation("spritesheet", getAnimation("p_ice_jump"),
			x, y, 0.35f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		break;
	case PLAYER_ICE_JUMP_RIGHT:
		if (m_imFrench)
			TextureManager::Instance()->playAnimation("spritesheet", getAnimation("p_french_jump"),
				x, y, 0.35f, 0, 255, true);
		else
			TextureManager::Instance()->playAnimation("spritesheet", getAnimation("p_ice_jump"),
			x, y, 0.35f, 0, 255, true);
		break;
	case PLAYER_ICE_FALL_LEFT:
		if (m_imFrench)
			TextureManager::Instance()->playAnimation("spritesheet", getAnimation("p_french_fall"),
				x, y, 0.35f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		else
			TextureManager::Instance()->playAnimation("spritesheet", getAnimation("p_ice_fall"),
			x, y, 0.35f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		break;
	case PLAYER_ICE_FALL_RIGHT:
		if (m_imFrench)
			TextureManager::Instance()->playAnimation("spritesheet", getAnimation("p_french_fall"),
				x, y, 0.35f, 0, 255, true);
		else
			TextureManager::Instance()->playAnimation("spritesheet", getAnimation("p_ice_fall"),
			x, y, 0.35f, 0, 255, true);
		break;
	case PLAYER_ICE_ATK_LEFT:
		if (m_imFrench)
			TextureManager::Instance()->playAnimation("spritesheet", getAnimation("p_french_atk"),
				x, y, 0.35f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		else
			TextureManager::Instance()->playAnimation("spritesheet", getAnimation("p_ice_atk"),
			x, y, 0.35f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		break;
	case PLAYER_ICE_ATK_RIGHT:
		if (m_imFrench)
			TextureManager::Instance()->playAnimation("spritesheet", getAnimation("p_french_atk"),
				x, y, 0.35f, 0, 255, true);
		else
			TextureManager::Instance()->playAnimation("spritesheet", getAnimation("p_ice_atk"),
			x, y, 0.35f, 0, 255, true);
		break;
	default:
		if (m_imFrench)
			TextureManager::Instance()->playAnimation("spritesheet", getAnimation("p_french_idle"),
				x, y, 0.10f, 0, 255, true);
		else
			TextureManager::Instance()->playAnimation("spritesheet", getAnimation("p_idle"),
			x, y, 0.10f, 0, 255, true);
		break;
	}
	
}

void Player::update()
{
	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_K))
		printCoords();

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_GRAVE) && !m_keyPressedRecently)
	{
		m_keyPressedRecently = true;
		m_imFrench = !m_imFrench;
	}

	if(m_keyPressedRecently)
	{
		m_keyPressTimer++;
		if(m_keyPressTimer == 20)
		{
			m_keyPressTimer = 0;
			m_keyPressedRecently = false;
		}
	}

	if (getHealthPoints() == 0)
		setIsDead(true);

	
	// TODO: Player movement has been moved here.
	// It has been moved because now the player movement is tied to the player,
	// instead of being tied to the LevelOne.

	// Parse player movement ------------------------------------------------------------------------------------------------------------------
	switch (m_state)
	{
	// ----------------------------------------------------------------------------------------------------------------------------------------	
	case STATE_IDLE:
		//if (!m_grounded)
		//	m_state = STATE_FALL;
		//m_maxVelocityY = 0;
		// Transition from Idle state to Run state.
		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A) || EventManager::Instance().isKeyDown(SDL_SCANCODE_D))
		{
			m_state = STATE_RUN;
			//std::cout << "Transition to Running..." << std::endl;
		}
		// Transition from Idle state to Jump state.
		else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_SPACE) && m_grounded == true)
		{
			setAccelRateY(-JUMPFORCE); // SetAccelY(-JUMPFORCE);
			setGrounded(false);
			m_state = STATE_JUMP;
			//std::cout << "Transition to Jumping..." << std::endl;
		}
		break;
	// ----------------------------------------------------------------------------------------------------------------------------------------	
	case STATE_RUN:
		m_walkSound++;

		if (m_walkSound > 10)
		{
			SoundManager::Instance().playSound("walk");
			m_walkSound = 0;
		}

		// Move left, constraints for left invisible wall:
		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A) && getTransform()->position.x > 0)
		{
			setAccelRateX(-1.5);
			if(!m_isAnimating)
			{
				if(getAlienBlaster() == true)
				{
					setAnimationState(PLAYER_AB_RUN_LEFT);
				}
				else
				{
					setAnimationState(PLAYER_RUN_LEFT);
				}
				
			}
			if (getFacingRight() == true)
			{
				setFacingRight(false);
			}
			//std::cout << "Running Left..." << std::endl;
		}
		// Move right, constraints for right invisible wall:
		else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D) && getTransform()->position.x < 3450 - getWidth())
		{
			setAccelRateX(1.5);
			if(!m_isAnimating)
			{
				if (m_hasAB == true)
				{
					setAnimationState(PLAYER_AB_RUN_RIGHT);
				}
				else
				{
					setAnimationState(PLAYER_RUN_RIGHT);
				}
			}
			if (getFacingRight() != true)
			{
				setFacingRight(true);
			}
			//std::cout << "Running Right..." << std::endl;
		}
		// Transition from Idle state to Jump state.
		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_SPACE) && m_grounded == true)
		{
			m_state = STATE_JUMP;
			//std::cout << "Jumping..." << std::endl;

			if(!m_isAnimating)
			{
				if(getFacingRight() == true)
				{
					if(getAlienBlaster() == true)
					{
						setAnimationState(PLAYER_AB_JUMP_UP_RIGHT);
					}
					else
					{
						setAnimationState(PLAYER_JUMP_UP_RIGHT);
					}
				}
				if(getFacingRight() != true)
				{
					if (getAlienBlaster() == true)
					{
						setAnimationState(PLAYER_AB_JUMP_UP_LEFT);
					}
					else
					{
						setAnimationState(PLAYER_JUMP_UP_LEFT);
					}
				}
				
			}
		}
		// Transition to idle.
		if (!EventManager::Instance().isKeyDown(SDL_SCANCODE_A) && !EventManager::Instance().isKeyDown(SDL_SCANCODE_D) && m_grounded == true)
		{
			m_state = STATE_IDLE;
			//std::cout << "Idling..." << std::endl;
			if(!m_isAnimating)
			{
				if (getFacingRight() == true)
				{
					if (getAlienBlaster() == true)
					{
						setAnimationState(PLAYER_AB_IDLE_RIGHT);
					}
					else
					{
						setAnimationState(PLAYER_IDLE_RIGHT);
					}
				}
				if (getFacingRight() != true)
				{
					if (getAlienBlaster() == true)
					{
						setAnimationState(PLAYER_AB_IDLE_LEFT);
					}
					else
					{
						setAnimationState(PLAYER_IDLE_LEFT);
					}
				}
			}
		}
		break;
	// ----------------------------------------------------------------------------------------------------------------------------------------	
	case STATE_JUMP:
		// Increment jump counter for each frame that STATE_JUMP is active.
		m_jumpTime++;
		if (m_jumpTime > 13)
			m_jumpTime = 13;
		//std::cout << getTransform()->position.y << std::endl;
		//std::cout << m_jumpTime << std::endl;
		// Grounded = false, because we are jumping.
		setGrounded(false);
		// Negative, so we go up.
		setAccelRateY(-JUMPFORCE);
		m_maxVelocityY = -15;
		
		//std::cout << "Jumping..." << std::endl;

		// If A/D are pressed, change direction.
		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A) && getTransform()->position.x > 0 && m_grounded == false)
		{
			setAccelRateX(-1.5);
			if (getFacingRight() == true)
			{
				setFacingRight(false);
			}
		}
		else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D) && getTransform()->position.x < 1280 - getWidth() && m_grounded == false)
		{
			setAccelRateX(1.5);
			if (getFacingRight() != true)
			{
				setFacingRight(true);
			}
		}
		
		// Animations based on L/R direction.
		if (!m_isAnimating) 
		{
			if (m_isFacingRight == false)
			{
				if (getAlienBlaster() == true)
				{
					setAnimationState(PLAYER_AB_JUMP_UP_LEFT);
				}
				else
				{
					setAnimationState(PLAYER_JUMP_UP_LEFT);
				}
			}
			else
			{
				if (getAlienBlaster() == true)
				{
					setAnimationState(PLAYER_AB_JUMP_UP_RIGHT);
				}
				else
				{
					setAnimationState(PLAYER_JUMP_UP_RIGHT);
				}
			}
		}

		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_SPACE) && m_grounded == false)
		{
			if (m_jumpTime >= 13)
			{
				SoundManager::Instance().playSound("jump");
				m_jumpTime = 0;
				m_state = STATE_FALL;
			}
		}
		else if (EventManager::Instance().isKeyUp(SDL_SCANCODE_SPACE) && m_grounded == false)
		{
			if (m_jumpTime >= 0)
			{
				SoundManager::Instance().playSound("jump");
				m_jumpTime = 0;
				m_state = STATE_FALL;
			}
		}
		break;
	// ----------------------------------------------------------------------------------------------------------------------------------------	
	case STATE_FALL:
		{
			// If we aren't grounded & 25 frames have not passed yet.
			//if (m_grounded == false && m_jumpTime < 25)
			//{
			//	m_jumpTime++;
			//	m_maxVelocityY = 10;						//If this whole segment is commented out, jumping is a lot smoother, check yourself.
			//	setAccelRateY(JUMPFORCE);
			//
			//}
			//std::cout << "Falling..." << std::endl;
			// Moving L/R as player is falling.
			if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A) && getTransform()->position.x > 0 && m_grounded == false)
			{
				setAccelRateX(-1.5);
				if (getFacingRight() == true)
				{
					setFacingRight(false);
				}
			}
			// Change direction.
			else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D) && getTransform()->position.x < 1280 - getWidth() && m_grounded == false)
			{
				setAccelRateX(1.5);
				if (getFacingRight() != true)
				{
					setFacingRight(true);
				}
			}
			// Handle animations based on L/R facing.
			if (!m_isAnimating) 
			{
				if(m_isFacingRight == false)
				{
					if (getAlienBlaster() == true)
					{
						setAnimationState(PLAYER_AB_FALL_LEFT);
					}
					else
					{
						setAnimationState(PLAYER_FALL_LEFT);
					}
				}
				else
				{
					if (getAlienBlaster() == true)
					{
						setAnimationState(PLAYER_AB_FALL_RIGHT);
					}
					else
					{
						setAnimationState(PLAYER_FALL_RIGHT);
					}
				}
			}

			// If grounded, switch to run state.
			if (getGrounded() == true)
			{
				m_jumpTime = 0;
				if (!m_isAnimating) 
				{
					if (m_isFacingRight == false)
					{
						if (getAlienBlaster() == true)
						{
							setAnimationState(PLAYER_AB_IDLE_LEFT);
						}
						else
						{
							setAnimationState(PLAYER_IDLE_LEFT);
						}
					}
					else
					{
						if (getAlienBlaster() == true)
						{
							setAnimationState(PLAYER_AB_IDLE_RIGHT);
						}
						else
						{
							setAnimationState(PLAYER_IDLE_RIGHT);
						}
					}
				}
				m_state = STATE_RUN;
			}
		}
	}
	
	// Player movement.
	m_velocityX += m_accelRateX;
	m_velocityX *= (m_grounded ? m_drag : 1.0);
	m_velocityX = std::min(std::max(m_velocityX, -m_maxVelocityX), m_maxVelocityX);
	getTransform()->position.x += m_velocityX;

	m_velocityY += m_accelRateY + m_gravity;
	m_velocityY = std::min(std::max(m_velocityY, -m_maxVelocityY), m_maxVelocityY);
	getTransform()->position.y += m_velocityY;

	m_accelRateX = m_accelRateY = 0.0;

	if (isDead() == true)
	{
		setMaxSpeed(0);
		if (getFacingRight() == true)
		{
			setAnimationState(PLAYER_DEATH_RIGHT);
		}
		else
		{
			setAnimationState(PLAYER_DEATH_LEFT);
		}
	}

	// This is so animations don't spam.
	if(m_isAnimating)
	{
		m_animationTimer++;
	}
	if(m_animationTimer == 30)
	{
		m_animationTimer = 0;
		m_isAnimating = false;
		
		if(!m_hasAB)
		{
			if(m_isFacingRight)
				setAnimationState(PLAYER_ICE_IDLE_RIGHT);
			else
				setAnimationState(PLAYER_ICE_IDLE_LEFT);
		}
		else
		{
			if (m_isFacingRight)
				setAnimationState(PLAYER_AB_IDLE_RIGHT);
			else
				setAnimationState(PLAYER_AB_IDLE_LEFT);
		}
	}
}

void Player::clean()
{
}

void Player::setDestination(const glm::vec2 destination)
{
	m_destination = destination;
}
void Player::setMaxSpeed(const float speed)
{
	m_maxSpeed = speed;
}

void Player::setMaxVelocityY(float maxY)
{
	m_maxVelocityY = maxY;
}

void Player::setOrientation(glm::vec2 orientation)
{
	m_orientation = orientation;
}

void Player::setRotation(float angle)
{
	m_rotationAngle = angle;
}

float Player::getRotation() const
{
	return m_rotationAngle;
}

void Player::setAlienBlaster(bool hasAB)
{
	this->m_hasAB = hasAB;
}

bool Player::getAlienBlaster() const
{
	return m_hasAB;
}

void Player::setJumping(bool isJump)
{
	this->m_isJumping = isJump;
}

bool Player::getJumping()
{
	return m_isJumping;
}

void Player::setGrounded(bool grounded)
{
	this->m_grounded = grounded;
}

bool Player::getGrounded()
{
	return m_grounded;
}

void Player::setFacingRight(bool facingRight)
{
	this->m_isFacingRight = facingRight;
}

bool Player::getFacingRight() const
{
	return m_isFacingRight;
}

void Player::setIsDead(bool isDead)
{
	m_isDead = isDead;
}

bool Player::isDead()
{
	return m_isDead;
}

void Player::getHit()
{
	m_isAnimating = true;
	if (m_isFacingRight)
		setAnimationState(PLAYER_HURT_RIGHT);
	else
		setAnimationState(PLAYER_HURT_LEFT);
}

void Player::setHealthPoints(bool addPoint)
{
	if (addPoint && m_healthPoints <= 5)
		m_healthPoints += 1;
	else if (!addPoint && m_healthPoints > 0)
		m_healthPoints -= 1;
}


int Player::getHealthPoints() const
{
	return m_healthPoints;
}

void Player::printCoords()
{
	std::cout << "--------------------" << std::endl;
	std::cout << " Current Position:" << std::endl;
	std::cout << " x: " << this->getTransform()->position.x << std::endl;
	std::cout << " y: " << this->getTransform()->position.y << std::endl;
	std::cout << "--------------------" << std::endl;
}


// ----------------------------------------------------------------------------------------------

void Player::stopMoving()
{
	stopMovingX();
	stopMovingY();
}

void Player::stopMovingX()
{
	m_velocityX = 0.0;
}

void Player::stopMovingY()
{
	m_velocityY = 0.0;
}

void Player::setAccelRateX(float a)
{
	m_accelRateX = a;
}

void Player::setAccelRateY(float a)
{
	m_accelRateY = a;
}

double Player::getVelocityX()
{
	return m_velocityX;
}

double Player::getVelocityY()
{
	return m_velocityY;
}

void Player::setPosX(float x)
{
	getTransform()->position.x = x;
}

void Player::setPosY(float y)
{
	getTransform()->position.y = y;
}

bool Player::canShoot()
{
	return m_canShoot;
}

void Player::setShoot(bool canShoot)
{
	this->m_canShoot = canShoot;
}

void Player::meleeAttack()
{
	if(!m_isAnimating)
	{
		m_isAnimating = true;
		if (getFacingRight() == true)
			setAnimationState(PLAYER_ICE_ATK_RIGHT);
		else
			setAnimationState(PLAYER_ICE_ATK_LEFT);
	}
	

}

// ------------------------------------------------------------------------------------------------

void Player::m_Move()
{
	// magnitude
	m_targetDirection = m_destination - getTransform()->position;

	// normalized direction
	m_targetDirection = Util::normalize(m_targetDirection);

	getRigidBody()->velocity = m_targetDirection * m_maxSpeed;

	getTransform()->position += getRigidBody()->velocity;
}

void Player::setAnimationState(const PlayerAnimationState new_state)
{
	m_currentAnimationState = new_state;
}

void Player::m_buildAnimations()
{
	// ------------------------------------------------- WALK ------------------------
	Animation walkAnimation = Animation(); // ADDED ANIMATIONS FOR PIGOO SPRITESHEET

	walkAnimation.name = "p_walk";
	walkAnimation.frames.push_back(getSpriteSheet()->getFrame("pigoo-walk-1"));
	walkAnimation.frames.push_back(getSpriteSheet()->getFrame("pigoo-walk-2"));
	walkAnimation.frames.push_back(getSpriteSheet()->getFrame("pigoo-walk-3"));
	walkAnimation.frames.push_back(getSpriteSheet()->getFrame("pigoo-walk-4"));
	walkAnimation.frames.push_back(getSpriteSheet()->getFrame("pigoo-walk-3"));

	setAnimation(walkAnimation);

	// ------------------------------------------------- IDLE ------------------------
	Animation idleAnimation = Animation();

	idleAnimation.name = "p_idle";
	idleAnimation.frames.push_back(getSpriteSheet()->getFrame("pigoo-idle"));

	setAnimation(idleAnimation);

	// ------------------------------------------------- JUMP ------------------------
	Animation jumpUpAnimation = Animation();

	jumpUpAnimation.name = "p_jumpup";
	jumpUpAnimation.frames.push_back(getSpriteSheet()->getFrame("pigoo-jump"));

	setAnimation(jumpUpAnimation);

	// ------------------------------------------------- FALL ------------------------
	Animation fallAnimation = Animation();

	fallAnimation.name = "p_fall";
	fallAnimation.frames.push_back(getSpriteSheet()->getFrame("pigoo-fall"));

	setAnimation(fallAnimation);

	// ------------------------------------------------- SWIM ------------------------
	Animation swimAnimation = Animation();

	swimAnimation.name = "p_swim";
	swimAnimation.frames.push_back(getSpriteSheet()->getFrame("pigoo-swim-4"));
	swimAnimation.frames.push_back(getSpriteSheet()->getFrame("pigoo-swim-3"));
	swimAnimation.frames.push_back(getSpriteSheet()->getFrame("pigoo-swim-2"));
	swimAnimation.frames.push_back(getSpriteSheet()->getFrame("pigoo-swim-1"));
	swimAnimation.frames.push_back(getSpriteSheet()->getFrame("pigoo-swim-2"));
	swimAnimation.frames.push_back(getSpriteSheet()->getFrame("pigoo-swim-3"));

	setAnimation(swimAnimation);

	// ------------------------------------------------- DEATH -----------------------
	Animation deathAnimation = Animation();

	deathAnimation.name = "p_death";
	deathAnimation.frames.push_back(getSpriteSheet()->getFrame("pigoo-death-1"));
	deathAnimation.frames.push_back(getSpriteSheet()->getFrame("pigoo-death-2"));
	deathAnimation.frames.push_back(getSpriteSheet()->getFrame("pigoo-death-3"));
	deathAnimation.frames.push_back(getSpriteSheet()->getFrame("pigoo-death-4"));
	deathAnimation.frames.push_back(getSpriteSheet()->getFrame("pigoo-death-4"));

	setAnimation(deathAnimation);

	// ------------------------------------------------- HURT ------------------------
	Animation hurtAnimation = Animation();

	hurtAnimation.name = "p_hurt";
	hurtAnimation.frames.push_back(getSpriteSheet()->getFrame("pigoo-hurt"));
	hurtAnimation.frames.push_back(getSpriteSheet()->getFrame("pigoo-idle"));
	hurtAnimation.frames.push_back(getSpriteSheet()->getFrame("pigoo-hurt"));

	setAnimation(hurtAnimation);



	// ------------------------------------------------------------------------------------------------------------------
	//            ALIEN BLASTER ANIMATIONS
	// ------------------------------------------------------------------------------------------------------------------

	// ------------------------------------------------- WALK ------------------------
	Animation walkABAnimation = Animation(); // ADDED ANIMATIONS FOR PIGOO SPRITESHEET

	walkABAnimation.name = "p_ab_walk";
	walkABAnimation.frames.push_back(getSpriteSheet()->getFrame("pigoo-AB-walk-1"));
	walkABAnimation.frames.push_back(getSpriteSheet()->getFrame("pigoo-AB-walk-2"));
	walkABAnimation.frames.push_back(getSpriteSheet()->getFrame("pigoo-AB-walk-3"));
	walkABAnimation.frames.push_back(getSpriteSheet()->getFrame("pigoo-AB-walk-4"));

	setAnimation(walkABAnimation);

	// ------------------------------------------------- IDLE ------------------------
	Animation idleABAnimation = Animation();

	idleABAnimation.name = "p_ab_idle";
	idleABAnimation.frames.push_back(getSpriteSheet()->getFrame("pigoo-AB-walk-1"));

	setAnimation(idleABAnimation);

	// ------------------------------------------------- JUMP ------------------------
	Animation jumpUpABAnimation = Animation();

	jumpUpABAnimation.name = "p_ab_jump";
	jumpUpABAnimation.frames.push_back(getSpriteSheet()->getFrame("pigoo-AB-jump"));

	setAnimation(jumpUpABAnimation);

	// ------------------------------------------------- FALL ------------------------ 
	
	Animation fallABAnimation = Animation();

	fallABAnimation.name = "p_ab_fall";
	fallABAnimation.frames.push_back(getSpriteSheet()->getFrame("pigoo-AB-fall"));

	setAnimation(fallABAnimation);
	
	// ------------------------------------------------- SWIM ------------------------
	Animation swimABAnimation = Animation();

	swimABAnimation.name = "p_ab_swim";
	swimABAnimation.frames.push_back(getSpriteSheet()->getFrame("pigoo-swim-AB-4"));
	swimABAnimation.frames.push_back(getSpriteSheet()->getFrame("pigoo-swim-AB-3"));
	swimABAnimation.frames.push_back(getSpriteSheet()->getFrame("pigoo-swim-AB-2"));
	swimABAnimation.frames.push_back(getSpriteSheet()->getFrame("pigoo-swim-AB-1"));
	swimABAnimation.frames.push_back(getSpriteSheet()->getFrame("pigoo-swim-AB-2"));
	swimABAnimation.frames.push_back(getSpriteSheet()->getFrame("pigoo-swim-AB-3"));

	setAnimation(swimABAnimation);
	// ------------------------------------------------------------------------------------------------------------------
	//            ICICLE ANIMATIONS
	// ------------------------------------------------------------------------------------------------------------------

	// ------------------------------------------------- IDLE ------------------------
	Animation icicleIdle = Animation();

	icicleIdle.name = "p_ice_idle";
	icicleIdle.frames.push_back(getSpriteSheet()->getFrame("pigoo-ice-atk-1"));

	setAnimation(icicleIdle);
	// ------------------------------------------------- WALK ------------------------
	Animation icicleWalk = Animation();

	icicleWalk.name = "p_ice_walk";
	icicleWalk.frames.push_back(getSpriteSheet()->getFrame("pigoo-ice-walk-1"));
	icicleWalk.frames.push_back(getSpriteSheet()->getFrame("pigoo-ice-walk-2"));
	icicleWalk.frames.push_back(getSpriteSheet()->getFrame("pigoo-ice-walk-3"));
	icicleWalk.frames.push_back(getSpriteSheet()->getFrame("pigoo-ice-walk-4"));

	setAnimation(icicleWalk);
	// ------------------------------------------------- JUMP ------------------------
	Animation icicleJump = Animation();

	icicleJump.name = "p_ice_jump";
	icicleJump.frames.push_back(getSpriteSheet()->getFrame("pigoo-ice-jump"));

	setAnimation(icicleJump);

	// ------------------------------------------------- FALL ------------------------
	Animation icicleFall = Animation();

	icicleFall.name = "p_ice_fall";
	icicleFall.frames.push_back(getSpriteSheet()->getFrame("pigoo-ice-fall"));

	setAnimation(icicleFall);

	// ------------------------------------------------- ATTACK ------------------------
	Animation icicleAtk = Animation();

	icicleAtk.name = "p_ice_atk";
	icicleAtk.frames.push_back(getSpriteSheet()->getFrame("pigoo-ice-atk-1"));
	icicleAtk.frames.push_back(getSpriteSheet()->getFrame("pigoo-ice-atk-2"));
	icicleAtk.frames.push_back(getSpriteSheet()->getFrame("pigoo-ice-atk-3"));
	icicleAtk.frames.push_back(getSpriteSheet()->getFrame("pigoo-ice-atk-4"));

	setAnimation(icicleAtk);

	// J'AIME MANGER DU POISSON

	// Aie
	Animation frenchHurt = Animation();

	frenchHurt.name = "p_french_hurt";
	frenchHurt.frames.push_back(getSpriteSheet()->getFrame("pigoo-hurt-f"));
	frenchHurt.frames.push_back(getSpriteSheet()->getFrame("pigoo-idle-f-2"));
	frenchHurt.frames.push_back(getSpriteSheet()->getFrame("pigoo-hurt-f"));

	setAnimation(frenchHurt);

	// Inactif - Baguette
	Animation frenchIdle = Animation();

	frenchIdle.name = "p_french_idle";
	frenchIdle.frames.push_back(getSpriteSheet()->getFrame("pigoo-idle-f"));

	setAnimation(frenchIdle);
	
	// Inactif - Le Blasteur
	Animation frenchIdleAB = Animation();

	frenchIdleAB.name = "p_french_idle_AB";
	frenchIdleAB.frames.push_back(getSpriteSheet()->getFrame("pigoo-AB-idle-f"));
	
	setAnimation(frenchIdleAB);
	
	// Sauter - Baguette
	Animation frenchJump = Animation();

	frenchJump.name = "p_french_jump";
	frenchJump.frames.push_back(getSpriteSheet()->getFrame("pigoo-jump-f"));

	setAnimation(frenchJump);

	// Sauter 
	Animation frenchJumpAB = Animation();

	frenchJumpAB.name = "p_french_jump_AB";
	frenchJumpAB.frames.push_back(getSpriteSheet()->getFrame("pigoo-AB-jump-f"));

	setAnimation(frenchJumpAB);
	
	// Tomber - Baguette
	Animation frenchFall = Animation();

	frenchFall.name = "p_french_fall";
	frenchFall.frames.push_back(getSpriteSheet()->getFrame("pigoo-fall-f"));

	setAnimation(frenchFall);

	// Tomber
	Animation frenchFallAB = Animation();

	frenchFallAB.name = "p_french_fall_AB";
	frenchFallAB.frames.push_back(getSpriteSheet()->getFrame("pigoo-AB-fall-f"));

	setAnimation(frenchFallAB);

	// Marcher - Baguette
	Animation frenchWalk = Animation();

	frenchWalk.name = "p_french_walk";
	frenchWalk.frames.push_back(getSpriteSheet()->getFrame("pigoo-walk-f-1"));
	frenchWalk.frames.push_back(getSpriteSheet()->getFrame("pigoo-walk-f-2"));
	frenchWalk.frames.push_back(getSpriteSheet()->getFrame("pigoo-walk-f-3"));
	frenchWalk.frames.push_back(getSpriteSheet()->getFrame("pigoo-walk-f-4"));

	setAnimation(frenchWalk);

	// Marcher
	Animation frenchWalkAB = Animation();

	frenchWalkAB.name = "p_french_walk_AB";
	frenchWalkAB.frames.push_back(getSpriteSheet()->getFrame("pigoo-AB-walk-f-1"));
	frenchWalkAB.frames.push_back(getSpriteSheet()->getFrame("pigoo-AB-walk-f-2"));
	frenchWalkAB.frames.push_back(getSpriteSheet()->getFrame("pigoo-AB-walk-f-3"));

	setAnimation(frenchWalkAB);
	
	// Claque avec du pain
	Animation frenchAttack = Animation();

	frenchAttack.name = "p_french_atk";
	frenchAttack.frames.push_back(getSpriteSheet()->getFrame("pigoo-atk-f-1"));
	frenchAttack.frames.push_back(getSpriteSheet()->getFrame("pigoo-atk-f-2"));
	frenchAttack.frames.push_back(getSpriteSheet()->getFrame("pigoo-atk-f-3"));
	frenchAttack.frames.push_back(getSpriteSheet()->getFrame("pigoo-atk-f-4"));

	setAnimation(frenchAttack);
	
	// La Mort
	Animation frenchDeath = Animation();

	frenchDeath.name = "p_french_death";
	frenchDeath.frames.push_back(getSpriteSheet()->getFrame("pigoo-death-f-1"));
	frenchDeath.frames.push_back(getSpriteSheet()->getFrame("pigoo-death-f-2"));
	frenchDeath.frames.push_back(getSpriteSheet()->getFrame("pigoo-death-f-3"));
	frenchDeath.frames.push_back(getSpriteSheet()->getFrame("pigoo-death-f-4"));
	frenchDeath.frames.push_back(getSpriteSheet()->getFrame("pigoo-death-f-4"));

	setAnimation(frenchDeath);
}
