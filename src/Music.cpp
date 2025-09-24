#include <SDL2/SDL.h>
#include <Music.h>
#include <Resources.h>
#include <iostream>

Music::Music() {
  music = nullptr;
}

Music::Music(std::string file) {
  music = nullptr;
  Open(file);
}

void Music::Open(std::string file) {
  Stop();
  
  music = Resources::GetMusic(file);
  if (music == nullptr) {
    std::cout << "Error: " << SDL_GetError() << std::endl;
    exit(1);
  }
}

void Music::Play(int times) {
  if (music != nullptr) {
    Mix_PlayMusic(music.get(), times);
  } else {
    SDL_Log("Music not loaded, unable to play!\n");
  }
}

void Music::Stop(int msToStop) {
  if (music != nullptr) {
    Mix_FadeOutMusic(msToStop);
  }
}

bool Music::isOpen() {
  return music != nullptr;
}

Music::~Music() {
  Stop();
}
