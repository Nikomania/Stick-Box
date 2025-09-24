#pragma once
#include <SDL2/SDL.h>

class Animation {
public:
  Animation(
    int frameStart=0,
    int frameEnd=0,
    float frameTime=0,
    SDL_RendererFlip flip = SDL_FLIP_NONE
  );

  int frameStart;
  int frameEnd;
  float frameTime;
  SDL_RendererFlip flip;
};
