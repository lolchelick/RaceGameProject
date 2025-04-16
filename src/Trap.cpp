#include "include/Trap.h"

Trap::Trap(float speed, std::string texturePath, const RenderWindow &win)
{
	Texture &t = TextureHolder::GetTexture(texturePath);
	m_Size = t.getSize();

	m_Sprite.setTexture(t);
	m_Sprite.setOrigin(m_Size.x, m_Size.y);
	m_Speed = speed;
	m_WinSize = win.getSize();

	/*m_Rect = FloatRect(m_Position.x - m_Size.x / 2.0f, m_Position.y - m_Size.y / 2.0f, m_Size.x, m_Size.y);*/

	srand(time(nullptr));
	int randSeed = (rand() % 10) + 1;
	m_Position = generateRandomPosition(randSeed);

	m_Sprite.setPosition(m_Position);
}

Vector2f Trap::generateRandomPosition(int seed)
{
	srand(time(nullptr) * seed);
	float posX = rand() % m_WinSize.x;
	float posY = -(rand() % 1000);
	m_Active = false;

	if (posX <= 0.0f + 1.5f * m_Size.x)
	{
		posX = 1.5f * m_Size.x;
	}
	else if (posX >= m_WinSize.x - 1.5f * m_Size.x)
	{
		posX = m_WinSize.x - 1.5f * m_Size.x;
	}
	return Vector2f(posX, posY);
}

bool Trap::isActive()
{
	return m_Active;
}

void Trap::update(float deltaTime)
{
	m_Position.y += deltaTime * m_Speed;

	if (m_Sprite.getPosition().y >= m_WinSize.y + m_Size.y / 2.0f)
	{
		srand(time(nullptr));
		float randSeed = rand() % 10 + 1;
		m_Position = generateRandomPosition(randSeed);
	}
	m_Sprite.setPosition(m_Position);
}

Sprite Trap::getSprite()
{
	return m_Sprite;
}

Vector2f Trap::getPosition()
{
	return m_Position;
}

FloatRect Trap::getRect()
{
	return m_Sprite.getGlobalBounds();
}