#include "include/Button.h"

Button::Button(Vector2f pos, std::string path)
{
	Texture &t = TextureHolder::GetTexture(path);
	m_Shape.setTexture(&t);
	m_Size = Vector2f(t.getSize().x, t.getSize().y);
	m_ActiveSize = Vector2f(m_Size.x * 1.5f, m_Size.y * 1.5f);
	m_Shape.setSize(m_Size);
	m_Shape.setOrigin(t.getSize().x / 2.0f, t.getSize().y / 2.0f);
	m_Position = pos;
	m_Shape.setPosition(m_Position);

	m_ShapeRect = FloatRect(pos.x, pos.y, t.getSize().x, t.getSize().y);
}

bool Button::update(const RenderWindow &win)
{
	Vector2i mousePos = Mouse::getPosition(win);
	if (mousePos.x >= m_Shape.getPosition().x - m_ShapeRect.width / 2.0f && mousePos.x <= m_Shape.getPosition().x +  m_ShapeRect.width / 2.0f &&
		mousePos.y >= m_Shape.getPosition().y - m_ShapeRect.height / 2.0f && mousePos.y <= m_Shape.getPosition().y + m_ShapeRect.height / 2.0f)
	{
		m_Shape.setRotation(60.0f);
		m_Shape.setSize(m_ActiveSize);
		m_Shape.setOrigin(m_ActiveSize.x / 2.0f, m_ActiveSize.y / 2.0f);
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			return true;
		}
	}
	else
	{
		m_Shape.setRotation(0.0f);
		m_Shape.setSize(m_Size);
		m_Shape.setOrigin(m_Size.x / 2.0f, m_Size.y / 2.0f);
	}

	m_Shape.setPosition(m_Position);
	return false;
}

const RectangleShape &Button::getShape()
{
	return m_Shape;
}