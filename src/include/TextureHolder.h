#pragma once

#include <SFML/Graphics.hpp>
#include <assert.h>
#include <map>
#include <string>
#include <iostream>

using namespace sf;

class TextureHolder
{
public:
	TextureHolder();
	static Texture &GetTexture(const std::string &pt);
private:
	static std::map<std::string, Texture> thMap;
	static TextureHolder *m_s_Instance;
};