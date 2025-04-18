#include "include/Player.h"

Player::Player(const Texture &texture, Vector2f pos, float speed)
{
	m_Sprite.setTexture(texture);
	m_SizeX = texture.getSize().x;
	m_Size = texture.getSize();
	m_Position = pos;
	m_Sprite.setPosition(m_Position);
	m_Sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
	m_Speed = speed;
	m_MoveState = moveState::GOING_STRAIGHT;
}

void Player::update(float deltaTime, const RenderWindow &win)
{
	
	if (Keyboard::isKeyPressed(Keyboard::LShift))
	{
		m_NitroCoeff = 3.0f;
	}
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		m_Position.x -= m_Speed * m_NitroCoeff * deltaTime;
		m_MoveState = moveState::MOVE_LEFT;
	}
	else if (Keyboard::isKeyPressed(Keyboard::D))
	{
		m_Position.x += m_Speed * m_NitroCoeff * deltaTime;
		m_MoveState = moveState::MOVE_RIGHT;
	}
	else
	{
		m_MoveState = moveState::GOING_STRAIGHT;
	}
	m_NitroCoeff = 1.0f;

	switch (m_MoveState)
	{
	case GOING_STRAIGHT:
		m_Sprite.setRotation(0);
		break;
	case MOVE_LEFT:
		m_Sprite.setRotation(-TURN_ROTATION_ANGLE);
		break;
	case MOVE_RIGHT:
		m_Sprite.setRotation(TURN_ROTATION_ANGLE);
		break;
	default:
		break;
	}

	if (m_Position.x <= 0.0f + m_SizeX / 2.0f)
		m_Position.x = 0.0f + m_SizeX / 2.0f;

	if(m_Position.x >= win.getSize().x - m_SizeX / 2.0f)
		m_Position.x = win.getSize().x - m_SizeX / 2.0f;

	m_Sprite.setPosition(m_Position);
}

Sprite Player::getSprite()
{
	return m_Sprite;
}

Vector2f Player::getPosition()
{
	return m_Position;
}

FloatRect Player::getRect()
{
	return m_Sprite.getGlobalBounds();
}

FloatRect Player::getCollisionRect()
{
	m_CollisionRect = FloatRect(m_Position.x + m_Size.x / 10.0f, m_Position.y + m_Size.y / 10.0f, m_Size.x - m_Size.x / 10.0f , m_Size.y - m_Size.y / 10.0f);
	return m_CollisionRect;
}