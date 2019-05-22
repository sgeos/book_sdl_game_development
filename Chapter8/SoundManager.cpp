#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include <iostream>
#include <map>
#include <string>
#include "SoundManager.h"

SoundManager *SoundManager::sInstance;

SoundManager::SoundManager() {
  Mix_OpenAudio(22050, AUDIO_S16, 2, 4096);
}

SoundManager::~SoundManager() {
  Mix_CloseAudio();
}

bool SoundManager::load(std::string pFilename, std::string pId, sound_type pType) {
  bool success;
  switch (pType) {
    case SOUND_MUSIC: {
      Mix_Music *music = Mix_LoadMUS(pFilename.c_str());
      success = nullptr != music;
      if (success) {
        mMusicList[pId] = music;
      } else {
        std::cout << "Could not load music: ERROR - " << Mix_GetError() << std::endl;
      }
      break;
    }
    case SOUND_SFX: {
      Mix_Chunk *chunk = Mix_LoadWAV(pFilename.c_str());
      success = nullptr != chunk;
      if (success) {
        mSoundEffectList[pId] = chunk;
      } else {
        std::cout << "Could not load SFX: ERROR - " << Mix_GetError() << std::endl;
      }
      break;
    }
    default: {
      success = false;
      break;
    }
  }
  return success;
}

void SoundManager::playMusic(std::string pId, int pLoopCount) {
  Mix_PlayMusic(mMusicList[pId], pLoopCount);
}

void SoundManager::playSoundEffect(std::string pId, int pLoopCount) {
  const int any_channel = -1;
  Mix_PlayChannel(any_channel, mSoundEffectList[pId], pLoopCount);
}

