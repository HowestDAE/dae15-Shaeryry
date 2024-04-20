#include "pch.h"
#include "Texture.h"
#include "TextureManager.h"
#include <iostream>

TextureManager::TextureManager()
	: m_Textures{}
{
}

TextureManager::~TextureManager()
{
	ClearTextures();
}

Texture* TextureManager::GetTexture(const std::string& key,const std::string& texturePath)
{
	Texture* foundTexture{ m_Textures[key] };
	
	if (foundTexture != nullptr) {
		//std::cout << "found " + key << std::endl;
		return foundTexture;
	} else {
		// Create texture and add it to the map to retrieve later !
		Texture* newTexture{ new Texture(texturePath) };
		m_Textures[key] = newTexture;
		//std::cout << "created " + key << std::endl;

		return newTexture;
	};

	return nullptr;
}

void TextureManager::DeleteTexture(Texture* textureToDelete)
{
	if (textureToDelete != nullptr) {
		delete textureToDelete;
	}
}

void TextureManager::ClearTextures()
{
	std::map<std::string, Texture*>::iterator it;

	for (it = m_Textures.begin(); it != m_Textures.end(); it++)
	{
		//std::cout << it->first << std::endl;
		DeleteTexture(it->second);
		m_Textures[it->first] = nullptr;
	}
}
