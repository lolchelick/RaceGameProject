#include "include/Biker.h"


Biker::Biker(std::string TexturePath, float speedCoeff, float BackSpeed, const RenderWindow &win)
{
	Texture &t = TextureHolder::GetTexture(TexturePath);
	m_Sprite.setTexture(t);
	m_Size = t.getSize();
	m_Sprite.setOrigin(m_Size.x, m_Size.y);
	m_SpeedCoeff = speedCoeff;
	M_BackSpeed = BackSpeed;
	WinSize = win.getSize();

	m_SpawnedUpward = true;
	goingRight = true;

	srand(time(nullptr));

	setRandomPosition(rand() % 4 + 1);
	setRandomTypeOfMovement();
}

void Biker::setRandomPosition(int seed)
{
	Vector2f randPos;
	srand(time(nullptr) * seed);
	randPos.x = rand() % WinSize.x + m_Size.x / 2.0f;
	randPos.y =  -(rand() % 4 + 1) * 100;
	m_Position = randPos;
}

void Biker::setRandomSpeedCoeff(int seed)
{
	srand(time(nullptr) * seed);
	
	m_SpeedCoeff = 2.0f + ((rand() % 10) / 10);
}

Sprite Biker::getSprite()
{
	return m_Sprite;
}

Vector2f Biker::getPosition()
{
	return m_Position;
}

FloatRect Biker::getRect()
{
	return m_Sprite.getGlobalBounds();
}


void Biker::update(float deltaTime)
{

	if(goingRight && m_Position.x >= WinSize.x - 2 * m_Size.x)
		goingRight = false;
	else if(!goingRight && m_Position.x <= 2 * m_Size.x)
		goingRight = true;

	m_Position.y += deltaTime * M_BackSpeed * m_SpeedCoeff;
	
	if(dead)
		mc = 0;
	else 
		mc = 1;

	if(goingRight)
		m_Position.x += deltaTime * M_BackSpeed * m_SpeedCoeff * m_MovementTypeX * mc;
	else
		m_Position.x -= deltaTime * M_BackSpeed * m_SpeedCoeff * m_MovementTypeX * mc;


	

	
	m_SpawnedUpward = false;

	if (m_Position.y >= WinSize.y + m_Size.y)
	{
		int seed = rand() % 5 + 1;
		setRandomPosition(seed);
		setRandomSpeedCoeff(seed);
		this->m_SpawnedUpward = true;
		setRandomTypeOfMovement();
		dead = false;
	}

	if (m_Position.x <= 0.0f + m_Size.x / 2.0f)
	{
		m_Position.x = m_Size.x;
	}
	else if (m_Position.x >= WinSize.x - m_Size.x / 2.0f)
	{
		m_Position.x = WinSize.x - m_Size.x;
	}


	m_Sprite.setPosition(m_Position);
}

bool Biker::isSpawnedUpward()
{
	return m_SpawnedUpward;
}

void Biker::setSprite(const Sprite &s)
{
	m_Sprite = s;
}

void Biker::setUnoSpeedCoeff()
{
	this->m_SpeedCoeff = 1.0f;
}

void Biker::setRandomTypeOfMovement()
{
	srand(time(nullptr));
	int randN = rand() % 3;

	switch (randN)
	{
	case 0:
		m_MovementTypeX = TypeOfMovement::STRAIGHT;
		break;
	case 1:
		m_MovementTypeX = TypeOfMovement::SLOW_SNAKE;
		break;
	case 2:
		m_MovementTypeX = TypeOfMovement::FAST_SNAKE;
		break;
	default:
		break;
	}
}


void Biker::setDead()
{
	dead = true;
}