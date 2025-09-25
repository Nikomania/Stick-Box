#include <Manager/SpriteRenderer.h>
#include <Core/GameObject.h>
#include <DataStructure/Component.h>
#include <iostream>

SpriteRenderer::SpriteRenderer(GameObject& associated) :Component(associated), sprite() {}

SpriteRenderer::SpriteRenderer(
  GameObject& associated,
  std::string file,
  int frameCountW = 1,
  int frameCountH = 1
) : Component(associated), sprite(file, frameCountW, frameCountH) {
  associated.box.w = sprite.GetWidth();
  associated.box.h = sprite.GetHeight();
}

SpriteRenderer::~SpriteRenderer() {}

void SpriteRenderer::SetFrameCount(int frameCountW, int frameCountH) {
  sprite.SetFrameCount(frameCountW, frameCountH);
}

void SpriteRenderer::SetScale(float scaleX, float scaleY) {
  sprite.SetScale(scaleX, scaleY);
  associated.box.x += associated.box.w / 2 * (1 - scaleX); // keep the center
  associated.box.y += associated.box.h / 2 * (1 - scaleY);
  associated.box.w = sprite.GetWidth();  // don't know if i should update box sizes
  associated.box.h = sprite.GetHeight();
}

void SpriteRenderer::SetFrame(int frame, SDL_RendererFlip flip) {
  sprite.SetFrame(frame);
  sprite.SetFlip(flip);
}

void SpriteRenderer::Open(std::string file) {
  sprite.Open(file);
  associated.box.w = sprite.GetWidth();
  associated.box.h = sprite.GetHeight();
}

void SpriteRenderer::Start() {}

void SpriteRenderer::Update(float dt) {}

void SpriteRenderer::Render() {
  sprite.Render(associated.box.x, associated.box.y, associated.angleDeg);
}

bool SpriteRenderer::Is(std::string type) {
  return type == "SpriteRenderer";
}

void SpriteRenderer::SetFrame(int frame) {
  sprite.SetFrame(frame);
}

void SpriteRenderer::SetCameraFollower(bool cameraFollower) {
  sprite.cameraFollower = cameraFollower;
}
