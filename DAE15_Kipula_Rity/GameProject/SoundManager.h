#pragma once
#include "pch.h"
#include <vector>
#include <map>

class SoundEffect;
class SoundManager final 
{
public:
	explicit SoundManager();
	SoundManager& operator=(const SoundManager& rhs) = delete;
	SoundManager(const SoundManager& other) = delete;
	SoundManager(SoundManager&& other) = delete;
	SoundManager& operator=(SoundManager&& other) = delete;
	~SoundManager();

	SoundEffect* GetSound(const std::string& soundName);
	void DeleteSound(SoundEffect* soundToDelete);
private:
	std::map<std::string, SoundEffect*> m_Sounds;
};

