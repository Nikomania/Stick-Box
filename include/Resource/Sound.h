#pragma once

#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <memory>

class Sound {
private:
  std::shared_ptr<Mix_Chunk> chunk;
  int channel;
public:
  Sound();
  Sound(std::string file);
  ~Sound();

  void Play(int times = 1);
  void Stop();
  void Open(std::string file);
  bool IsOpen();
};
