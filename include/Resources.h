#pragma once

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <memory>
#include <iostream>
#include <unordered_map>

class Resources {
private:
  static std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> imageTable;
  static std::unordered_map<std::string, std::shared_ptr<Mix_Music>> musicTable;
  static std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>> soundTable;
  static std::unordered_map<std::string, std::shared_ptr<TTF_Font>> fontTable;

  template <typename T>
  static void ClearResource(
    std::unordered_map<std::string, std::shared_ptr<T>>& table,
    std::string resource_name
  );

  template <typename T>
  static std::shared_ptr<T> SetResource(
    std::unordered_map<std::string, std::shared_ptr<T>>& table,
    T* resource,
    void (*FreeResource)(T*),
    std::string file,
    std::string key,
    std::string resource_name
  );
public:
  static std::shared_ptr<SDL_Texture> GetImage(std::string file);
  static void ClearImages();

  static std::shared_ptr<Mix_Music> GetMusic(std::string file);
  static void ClearMusics();

  static std::shared_ptr<Mix_Chunk> GetSound(std::string file);
  static void ClearSounds();

  static std::shared_ptr<TTF_Font> GetFont(std::string file, int fontSize);
  static void ClearFonts();
};
