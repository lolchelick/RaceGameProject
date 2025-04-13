#include "include/Background.h"



Background::Background(Texture *t, Vector2f size, bool active, Vector2f pos, float speed)
{
	m_Shape.setSize(size);
	m_Shape.setTexture(t);
	this->m_Active = active;
	m_Position = pos;
	this->m_Shape.setPosition(m_Position);
	m_Speed = speed;
}

void Background::setPosition(Vector2f pos)
{
	m_Position = pos;
}

void Background::update(float deltaTime, const RenderWindow &win)
{
		m_Position.y += m_Speed * deltaTime;
		m_Shape.setPosition(m_Position);

}

Vector2f Background::getPosition()
{
	return m_Position;
}

Vector2f Background::getSize()
{
	return m_Shape.getSize();
}

RectangleShape Background::getShape()
{
	return m_Shape;
}
