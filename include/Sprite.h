#pragma once

#include <SDL2/SDL.h>
#include <Vec2.h>
#include <iostream>
#include <memory>

class Sprite {
  private:
    std::shared_ptr<SDL_Texture> texture;
  
    int width;
    int height;
    int frameCountW;
    int frameCountH;

    SDL_Rect clipRect;
    SDL_RendererFlip flip;
    Vec2 scale;
  public:
    bool cameraFollower;

    Sprite(bool cameraFollower = false);
    Sprite(
      std::string file,
      int frameCountW = 1,
      int frameCountH = 1,
      bool cameraFollower = false
    );
    ~Sprite();

    void Open(std::string file);
    void SetClip(int x, int y, int w, int h);
    void SetScale(float scaleX, float scaleY);
    Vec2 GetScale();
    void SetFlip(SDL_RendererFlip flip);
    void Render(int x, int y, float angle = 0);
    void Render(int x, int y, int w, int h, float angle = 0);
    void SetFrame(int frame);
    void SetFrameCount(int frameCountW, int frameCountH);
    int GetWidth();
    int GetHeight();
    bool IsOpen();
};