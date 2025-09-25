#include <Resource/Sprite.h>
#include <Core/Game.h>
#include <Manager/Resources.h>
#include <SDL2/SDL_image.h>
#include <HUD/Camera.h>
#include <iostream>

Sprite::Sprite(
  bool cameraFollower
) : 
  cameraFollower(cameraFollower),
  texture(nullptr),
  width(0),
  height(0),
  frameCountW(1),
  frameCountH(1),
  flip(SDL_FLIP_NONE),
  scale(1, 1)
{}

Sprite::Sprite(
  std::string file,
  int frameCountW,
  int frameCountH,
  bool cameraFollower
) :
  cameraFollower(cameraFollower),
  texture(nullptr),
  width(0),
  height(0),
  frameCountW(frameCountW),
  frameCountH(frameCountH),
  flip(SDL_FLIP_NONE),
  scale(1, 1)
{
  Open(file);
}

Sprite::~Sprite() {}

void Sprite::Open(std::string file) {
  texture = Resources::GetImage(file);
  if (texture == nullptr) {
    std::cout << "Error: " << SDL_GetError() << std::endl;
    exit(1);
  }

  SDL_QueryTexture(texture.get(), nullptr, nullptr, &width, &height);
  SetClip(0, 0, width, height);
}

void Sprite::SetClip(int x, int y, int w, int h) {
  clipRect.x = x;
  clipRect.y = y;
  clipRect.w = w;
  clipRect.h = h;
}

void Sprite::SetScale(float scaleX, float scaleY) {
  scale.x = scaleX; // Mantenha a escala em dado eixo se o valor passado para ela for 0???
  scale.y = scaleY;
}

Vec2 Sprite::GetScale() {
  return scale;
}

void Sprite::SetFlip(SDL_RendererFlip flip) {
  this->flip = flip;
}

void Sprite::Render(int x, int y, float angle) {
  Render(x, y, clipRect.w, clipRect.h, angle);
}

void Sprite::Render(int x, int y, int w, int h, float angle) {
  SDL_Rect dst_rect;
  dst_rect.x = x + (cameraFollower? 0 : - 1) * Camera::pos.x;
  dst_rect.y = y + (cameraFollower? 0 : - 1) * Camera::pos.y;
  dst_rect.w = w * scale.x;
  dst_rect.h = h * scale.y;
  SDL_RenderCopyEx(
    Game::GetInstance().GetRenderer(),
    texture.get(),
    &clipRect,
    &dst_rect,
    angle,
    nullptr,
    flip
  );
}

void Sprite::SetFrame(int frame) {
  int w = GetWidth() / scale.x;
  int h = GetHeight() / scale.y;
  
  int x = (frame % frameCountW) * w;
  int y = (frame / frameCountW) * h;
  
  if (x + w <= width && y + h <= height) {
    SetClip(x, y, w, h);
  } else {
    std::cout << "Error: Frame out of bounds" << std::endl;
    exit(1);
  }
}

void Sprite::SetFrameCount(int frameCountW, int frameCountH) {
  this->frameCountW = frameCountW;
  this->frameCountH = frameCountH;
}

int Sprite::GetWidth() {
  return (width / frameCountW) * scale.x;
}

int Sprite::GetHeight() {
  return height / frameCountH * scale.y;
}

bool Sprite::IsOpen() {
  return texture != nullptr;
}
