#include <Game.h>
#include <GameObject.h>

int main(int argc, char** argv) {
  Game* game = &Game::GetInstance();

  game->Run();

  delete game;

  return 0;
}
