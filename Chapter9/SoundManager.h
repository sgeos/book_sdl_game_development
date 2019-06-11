#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include <map>
#include <string>

enum sound_type {
  SOUND_OFF = 0,
  SOUND_MUSIC = 1,
  SOUND_SFX = 2
};

class SoundManager {
  public:
    static SoundManager *Instance(void) {
      if (nullptr == sInstance) {
        sInstance = new SoundManager();
      }
      return sInstance;
    }
    bool load(std::string pFilename, std::string pId, sound_type pType);
    void playMusic(std::string pId, int pLoopCount);
    void playSoundEffect(std::string pId, int pLoopCount);

  private:
    static SoundManager *sInstance;
    std::map<std::string, Mix_Chunk *> mSoundEffectList;
    std::map<std::string, Mix_Music *> mMusicList;

    SoundManager();
    ~SoundManager();
    SoundManager(const SoundManager &);
    SoundManager &operator=(const SoundManager &);
};

#endif // SOUND_MANAGER_H

