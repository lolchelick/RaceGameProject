#pragma once
#include <SFML/Graphics.hpp>
#include "TextureHolder.h"

using namespace sf;

class Background
{
public:
	Background(Texture *t, Vector2f size, bool active, Vector2f pos, float speed);
	void update(float deltaTime, const RenderWindow& win);
	void setPosition(Vector2f pos);
	Vector2f getPosition();
	Vector2f getSize();
	RectangleShape getShape();
private:
	RectangleShape m_Shape;
	Vector2f m_Position;
	float m_Speed;
	bool m_Active;
};