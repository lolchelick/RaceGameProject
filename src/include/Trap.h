#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "TextureHolder.h"

using namespace sf;


class Trap
{
private:
	float m_Speed;
	Vector2f m_Position;
	Sprite m_Sprite;
	Vector2f generateRandomPosition(int seed);
	bool m_Active;
	Vector2u m_WinSize;
	Vector2u m_Size;
public:
	Trap(float speed, std::string texturePath, const RenderWindow &win);
	bool isActive();
	void update(float deltaTime);
	Sprite getSprite();
	Vector2f getPosition();
	FloatRect getRect();
};
