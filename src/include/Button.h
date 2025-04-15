#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "TextureHolder.h"

using namespace sf;

class Button
{
private:
	Vector2f m_Position;
	RectangleShape m_Shape;
	FloatRect m_ShapeRect;
public:
	Button(Vector2f pos, std::string path);
	bool update(const RenderWindow &win);
	const RectangleShape &getShape();
};