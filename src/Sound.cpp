#include <Sound.h>
#include <Resources.h>

Sound::Sound() {
  chunk = nullptr;
  channel = -1;
}

Sound::Sound(std::string file) {
  chunk = nullptr;
  channel = -1;
  Open(file);
}

Sound::~Sound() {} // can't halt the channel when destroying the sound, cause sound has already been freed from memory in resources

void Sound::Play(int times) {
  if (IsOpen()) {
    // -1 channel will get the first available channel and return it
    channel = Mix_PlayChannel(-1, chunk.get(), times - 1);
    if (channel == -1) {
      std::cout << "Error: " << SDL_GetError() << std::endl;
      exit(1);
    }
  } else {
    std::cout << "Error: Sound not loaded" << std::endl;
    exit(1);
  }
}

void Sound::Stop() {
  // check if the channel has already been halted
  if (IsOpen() && channel != -1) {
    Mix_HaltChannel(channel);
    channel = -1;
  }
}

void Sound::Open(std::string file) {
  Stop();

  chunk = Resources::GetSound(file);
  if (!IsOpen()) {
    std::cout << "Error: " << SDL_GetError() << std::endl;
    exit(1);
  }
}

bool Sound::IsOpen() {
  return chunk != nullptr;
}
