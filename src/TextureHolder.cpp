#include "include/TextureHolder.h"

TextureHolder *TextureHolder::m_s_Instance = nullptr;
std::map<std::string, Texture> TextureHolder::thMap;

TextureHolder::TextureHolder()
{
	assert(m_s_Instance == nullptr);
	m_s_Instance = this;
}

Texture &TextureHolder::GetTexture(const std::string &pt)
{
    auto& m = thMap;
    auto keyValuePair = m.find(pt);
    if (keyValuePair != m.end())
    {

        return keyValuePair->second;
    }
    else
    {

        Texture &texture = m[pt];
        if (!texture.loadFromFile(pt))
        {
           std::cout << "ERROR LOADING TEXTURE FROM <<<<" << pt << ">>>> INTO THE TEXTURE_HOLDER" << std::endl;
        }
        return texture;
    }
}