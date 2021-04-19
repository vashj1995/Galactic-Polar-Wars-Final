#include "BlasterBullet.h"
#include "Game.h"
#include "Util.h"
#include "SoundManager.h"

// Default Constructor.
BlasterBullet::BlasterBullet()
{
	TextureManager::Instance()->load("../Assets/textures/AB_Bullet.png", "bullet");

	const auto size = TextureManager::Instance()->getTextureSize("bullet");
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

	//SoundManager::Instance().load("../Assets/audio/BlasterSound.mp3", "blaster", SOUND_SFX); // added sound fx for collision
}

BlasterBullet::BlasterBullet(glm::vec2 position, bool direction, BulletType type) : m_direction(direction), m_type(type)
{
	glm::vec2 size;
	
	switch (m_type)
	{
	case ALIEN:
		TextureManager::Instance()->load("../Assets/textures/AB_Bullet.png", "AB_bullet");
		size = TextureManager::Instance()->getTextureSize("AB_bullet");
		
		//// Sound effects:
		//SoundManager::Instance().load("../Assets/audio/BlasterSound.mp3", "blaster", SOUND_SFX);
		break;
	case ICE:
		TextureManager::Instance()->load("../Assets/textures/IB_Bullet.png", "IB_bullet");
		size = TextureManager::Instance()->getTextureSize("IB_bullet");
		// Sound effects:
		// Load ice blaster sound here.
		//SoundManager::Instance().load("../Assets/audio/IceBlasterSound.mp3", "iceblaster", SOUND_SFX);
		break;
	}
	
	setWidth(size.x);
	setHeight(size.y);
	// Set the position to the value passed in to the Constructor.
	getTransform()->position = position;
	getRigidBody()->velocity = glm::vec2(0, 0);
	getRigidBody()->isColliding = false;
	
	setType(BULLET);
	setOrientation(glm::vec2(0.0f, 0.0f));
}

BlasterBullet::~BlasterBullet()
= default;


void BlasterBullet::draw()
{
	switch (m_type)
	{
	case ALIEN:
		if(m_direction == true)
			TextureManager::Instance()->draw("AB_bullet", getTransform()->draw_position.x, getTransform()->draw_position.y, 0, 255);
		if(m_direction == false)
			TextureManager::Instance()->draw("AB_bullet", getTransform()->draw_position.x, getTransform()->draw_position.y, 0, 255, false, SDL_FLIP_HORIZONTAL);
		break;
	case ICE:
		if (m_direction == true)
			TextureManager::Instance()->draw("IB_bullet", getTransform()->draw_position.x, getTransform()->draw_position.y, 0, 255);
		if (m_direction == false)
			TextureManager::Instance()->draw("IB_bullet", getTransform()->draw_position.x, getTransform()->draw_position.y, 0, 255, false, SDL_FLIP_HORIZONTAL);
		break;
	}

}

void BlasterBullet::update()
{
	m_checkBounds();
	m_Move();
	if(m_direction == true)
	{
		getTransform()->position += glm::vec2(25.0f, 0.0f);
	}
	else if(m_direction == false)
	{
		getTransform()->position -= glm::vec2(25.0f, 0.0f);
	}
}

void BlasterBullet::clean()
{
}

void BlasterBullet::setDestination(glm::vec2 destination)
{
	m_destination = destination;
}
void BlasterBullet::setMaxSpeed(float speed)
{
	m_maxSpeed = speed;
}
void BlasterBullet::setAccelerationRate(float rate)
{
	m_accelerationRate = rate;
}
void BlasterBullet::setOrientation(const glm::vec2 orientation)
{
	m_orientation = orientation;
}

float BlasterBullet::getAccelerationRate() const
{
	return m_accelerationRate;
}
glm::vec2 BlasterBullet::getOrientation() const
{
	return m_orientation;
}

void BlasterBullet::m_checkBounds()
{
}

void BlasterBullet::m_reset()
{
}

void BlasterBullet::m_Move()
{
	auto deltaTime = TheGame::Instance()->getDeltaTime();

	getRigidBody()->acceleration = getOrientation() * getAccelerationRate();

	getRigidBody()->velocity += getOrientation() * (deltaTime)+
		0.5f * getRigidBody()->acceleration * (deltaTime);

	getRigidBody()->velocity = Util::clamp(getRigidBody()->velocity, m_maxSpeed);

	getTransform()->position += getRigidBody()->velocity;

}
