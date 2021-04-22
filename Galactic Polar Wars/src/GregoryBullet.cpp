#include "GregoryBullet.h"
#include "Game.h"
#include "Util.h"
#include "SoundManager.h"

// Default Constructor.
GregoryBullet::GregoryBullet()
{
	TextureManager::Instance()->load("../Assets/textures/Gregory_Bullet.png", "G_bullet");

	const auto size = TextureManager::Instance()->getTextureSize("G_bullet");
	setWidth(size.x);
	setHeight(size.y);
	getTransform()->position = glm::vec2(100.0f, 400.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;

	setType(BULLET);
	setMaxSpeed(12.0f);
	setOrientation(glm::vec2(0.0f, -1.0f));
	setAccelerationRate(10.0f);

	SoundManager::Instance().load("../Assets/audio/BlasterSound.mp3", "blaster", SOUND_SFX);
}

GregoryBullet::GregoryBullet(glm::vec2 position, bool direction, TYPE type) : m_direction(direction)
{
	glm::vec2 size;

	TextureManager::Instance()->load("../Assets/textures/Gregory_Bullet.png", "G_bullet");
	size = TextureManager::Instance()->getTextureSize("G_bullet");

	// Sound effects:
	SoundManager::Instance().load("../Assets/audio/BlasterSound.mp3", "blaster", SOUND_SFX);

	setWidth(size.x);
	setHeight(size.y);
	// Set the position to the value passed in to the Constructor.
	getTransform()->position = position;
	getRigidBody()->velocity = glm::vec2(0, 0);
	getRigidBody()->isColliding = false;

	m_type = type;

	setType(BULLET);
	setOrientation(glm::vec2(0.0f, 0.0f));
}

GregoryBullet::~GregoryBullet()
= default;


void GregoryBullet::draw()
{
		if (m_direction == true)
			TextureManager::Instance()->draw("G_bullet", getTransform()->draw_position.x, getTransform()->draw_position.y, 0, 255);
		if (m_direction == false)
			TextureManager::Instance()->draw("G_bullet", getTransform()->draw_position.x, getTransform()->draw_position.y, 0, 255, false, SDL_FLIP_HORIZONTAL);
}

void GregoryBullet::update()
{
	m_checkBounds();
	m_Move();
	if (m_type == HORIZONTAL)
	{
		if (m_direction == true)
		{
			getTransform()->position += glm::vec2(12.0f, 0.0f);
		}
		else if (m_direction == false)
		{
			getTransform()->position -= glm::vec2(12.0f, 0.0f);
		}
	}
	else if (m_type == DIAGONAL_UP)
	{
		if (m_direction == true)
		{
			getTransform()->position += glm::vec2(12.0f, -1.8f);
		}
		else if (m_direction == false)
		{
			getTransform()->position -= glm::vec2(12.0f, 1.8f);
		}
	}
	else if (m_type == DIAGONAL_DOWN)
	{
		if (m_direction == true)
		{
			getTransform()->position += glm::vec2(12.0f, 1.8f);
		}
		else if (m_direction == false)
		{
			getTransform()->position -= glm::vec2(12.0f, -1.8f);
		}
	}
}

void GregoryBullet::clean()
{
}

void GregoryBullet::setDestination(glm::vec2 destination)
{
	m_destination = destination;
}
void GregoryBullet::setMaxSpeed(float speed)
{
	m_maxSpeed = speed;
}
void GregoryBullet::setAccelerationRate(float rate)
{
	m_accelerationRate = rate;
}
void GregoryBullet::setOrientation(const glm::vec2 orientation)
{
	m_orientation = orientation;
}

float GregoryBullet::getAccelerationRate() const
{
	return m_accelerationRate;
}
glm::vec2 GregoryBullet::getOrientation() const
{
	return m_orientation;
}

void GregoryBullet::m_checkBounds()
{
}

void GregoryBullet::m_reset()
{
}

void GregoryBullet::m_Move()
{
	auto deltaTime = TheGame::Instance()->getDeltaTime();

	getRigidBody()->acceleration = getOrientation() * getAccelerationRate();

	getRigidBody()->velocity += getOrientation() * (deltaTime)+
		0.5f * getRigidBody()->acceleration * (deltaTime);

	getRigidBody()->velocity = Util::clamp(getRigidBody()->velocity, m_maxSpeed);

	getTransform()->position += getRigidBody()->velocity;

}