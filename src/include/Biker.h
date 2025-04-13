#pragma once 
#include <SFML/Graphics.hpp>
#include <string>
#include "TextureHolder.h"
#include <iostream>

using namespace sf;

class Biker
{
public:
	Biker(std::string TexturePath, float speedCoeff, float BackSpeed, const RenderWindow& win);
	void update(float deltaTime);
	Sprite getSprite();
	Vector2f getPosition();
	FloatRect getRect();
	bool isSpawnedUpward();
	void setSprite(const Sprite &s);
	void setUnoSpeedCoeff();
private:
	float m_SpeedCoeff; // The effect of movement in the game is organised by moving of the background
	Sprite m_Sprite;
	static enum TypeOfMovement{STRAIGHT, SLOW_SNAKE, FAST_SNAKE};
	TypeOfMovement m_MovementTypeX = TypeOfMovement::STRAIGHT;
	Vector2u m_Size;
	Vector2f m_Position;
	float M_BackSpeed;
	Vector2u WinSize;
	void setRandomPosition(int seed);
	void setRandomSpeedCoeff(int seed);
	bool m_SpawnedUpward;
};
