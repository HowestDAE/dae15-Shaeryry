#pragma once
#include <Texture.h>
#include <map>

class TextureManager
{
public:
	TextureManager();
	~TextureManager();
	Texture* GetTexture(const std::string& key,const std::string& texturePath);
	void DeleteTexture(Texture* textureToDelete);
	void ClearTextures();
private:
	std::map<std::string,Texture*> m_Textures;
};

