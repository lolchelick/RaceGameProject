#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Player
{
public:
	Player(const Texture &t, Vector2f pos, float speed);
	void update(float deltaTime, const RenderWindow &win);
	Sprite getSprite();
	Vector2f getPosition();
	FloatRect getRect();
	FloatRect getCollisionRect();
private:
	Sprite m_Sprite;
	Vector2f m_Position;
	float m_Speed;
	enum moveState{GOING_STRAIGHT, MOVE_RIGHT, MOVE_LEFT};
	moveState m_MoveState;
	const int TURN_ROTATION_ANGLE = 17;
	float m_SizeX;
	float m_NitroCoeff = 1.0f;
	FloatRect m_CollisionRect;
	Vector2u m_Size;
};