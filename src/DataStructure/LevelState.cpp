#include <DataStructure/LevelState.h>
#include <SDL2/SDL.h>

LevelState::LevelState(exit_t playerEntrance) :
State(),
playerEntrance(playerEntrance),
exits() {
  SDL_Log("LevelState created!\n");
}

LevelState::~LevelState() {
  exits.clear();
}
