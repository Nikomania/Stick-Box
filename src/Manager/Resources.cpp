#include <Manager/Resources.h>
#include <Core/Game.h>

std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> Resources::imageTable;
std::unordered_map<std::string, std::shared_ptr<Mix_Music>> Resources::musicTable;
std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>> Resources::soundTable;
std::unordered_map<std::string, std::shared_ptr<TTF_Font>> Resources::fontTable;

template <typename T>
void Resources::ClearResource(std::unordered_map<std::string, std::shared_ptr<T>>& table, std::string resource_name) {
  std::vector<std::string> toRemove;
  for (auto& elem : table) {
    if (elem.second.use_count() == 1) {
      std::cout << "Removing " << resource_name << " " << elem.first << std::endl;
      toRemove.push_back(elem.first);
    } else {
      std::cout << "Keeping " << resource_name << " " << elem.first << " with use count " << elem.second.use_count() << std::endl;
    }
  }

  for (auto& i : toRemove) {
    table.erase(i);
  }
}

template <typename T>
std::shared_ptr<T> Resources::SetResource(
  std::unordered_map<std::string, std::shared_ptr<T>>& table,
  T* resource,
  void (*FreeResource)(T*),
  std::string file,
  std::string key,
  std::string resource_name
) {
  if (table.find(key) == table.end()) {
    SDL_Log("Loading %s from %s\n", resource_name.c_str(), file.c_str());
    std::shared_ptr<T> resource_shr(resource, FreeResource);
    if (resource_shr == nullptr) {
      std::cout << "Error: " << TTF_GetError() << std::endl;
      exit(1);
    }
    table[key] = resource_shr;
  }
  return table[key];
}

std::shared_ptr<SDL_Texture> Resources::GetImage(std::string file) {
  return SetResource(
    imageTable,
    IMG_LoadTexture(
      Game::GetInstance().GetRenderer(),
      file.c_str()
    ),
    SDL_DestroyTexture,
    file,
    file,
    "image"
  );
}

void Resources::ClearImages() {
  ClearResource<SDL_Texture>(imageTable, "image");
}

std::shared_ptr<Mix_Music> Resources::GetMusic(std::string file) {
  return SetResource(
    musicTable,
    Mix_LoadMUS(file.c_str()),
    Mix_FreeMusic,
    file,
    file,
    "music"
  );
}

void Resources::ClearMusics() {
  ClearResource<Mix_Music>(musicTable, "music");
}

std::shared_ptr<Mix_Chunk> Resources::GetSound(std::string file) {
  return SetResource(
    soundTable,
    Mix_LoadWAV(file.c_str()),
    Mix_FreeChunk,
    file,
    file,
    "sound"
  );
}

void Resources::ClearSounds() {
  ClearResource<Mix_Chunk>(soundTable, "sound");
}

std::shared_ptr<TTF_Font> Resources::GetFont(std::string file, int fontSize) {
  return SetResource(
    fontTable,
    TTF_OpenFont(file.c_str(), fontSize),
    TTF_CloseFont,
    file,
    file + std::to_string(fontSize),
    "font"
  );
}

void Resources::ClearFonts() {
  ClearResource<TTF_Font>(fontTable, "font");
}
