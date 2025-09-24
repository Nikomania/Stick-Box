#pragma once

#include <SDL2/SDL.h>
#include <State.h>
#include <iostream>
#include <stack>
#include <memory>

class Game {
public:
  static Game& GetInstance();
  State& GetCurrentState();
  SDL_Renderer* GetRenderer();

  void Push(State* state);

  void Run();

  float GetDeltaTime();

  ~Game();
private:
  Game(std::string title, int width, int height);
  void CalculateDeltaTime();

  void ClearStack();

  int frameStart;
  float dt;

  static Game* instance;

  State* storedState;
  SDL_Window* window;
  SDL_Renderer* renderer;
  std::stack<std::unique_ptr<State>> stateStack;
};
