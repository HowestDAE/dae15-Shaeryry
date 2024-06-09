#include "pch.h"
#include "SoundEffect.h"
#include "SoundManager.h"

SoundManager::SoundManager() :
    m_Sounds{}
{
}

SoundManager::~SoundManager()
{
    std::map<std::string, SoundEffect*>::iterator it;

    for (it = m_Sounds.begin(); it != m_Sounds.end(); it++)
    {
        DeleteSound(it->second);
        m_Sounds[it->first] = nullptr;
    }
}

SoundEffect* SoundManager::GetSound(const std::string& soundName)
{
    const std::string path{ "Sounds/" + soundName + ".wav" };
    SoundEffect* Sound{ m_Sounds[path] };

    if (Sound == nullptr) {
        Sound = new SoundEffect(path);
        m_Sounds[path] = Sound;
    }

    Sound->SetVolume(0.5f);

    return Sound;
}

void SoundManager::DeleteSound(SoundEffect* soundToDelete)
{
    if (soundToDelete != nullptr) {
        delete soundToDelete;
    }
}