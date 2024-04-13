#pragma once
#include "pch.h"
#include <Texture.h>
#include <map>

class TextureManager final {
public:
	explicit TextureManager();
	TextureManager& operator=(const TextureManager& rhs) = delete;
	TextureManager(const TextureManager& other) = delete;
	~TextureManager();

	Texture* GetTexture(const std::string& key,const std::string& texturePath);
	void DeleteTexture(Texture* textureToDelete);
	void ClearTextures();
private:
	std::map<std::string,Texture*> m_Textures;
};

