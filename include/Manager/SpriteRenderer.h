#pragma once
#include <Core/GameObject.h>
#include <DataStructure/Component.h>
#include <DataStructure/Animation.h>
#include <Resource/Sprite.h>
#include <iostream>

class SpriteRenderer : public Component {
private:
  Sprite sprite;
public:
  SpriteRenderer(GameObject& associated);
  SpriteRenderer(
    GameObject& associated,
    std::string file,
    int frameCountW,
    int frameCountH
  );
  ~SpriteRenderer();

  void Open(std::string file);
  void SetFrameCount(int frameCountW, int frameCountH);
  void SetScale(float scaleX, float scaleY);
  void SetFrame(int frame, SDL_RendererFlip flip);
  void Start() override;
  void Update(float dt) override;
  void Render() override;
  bool Is(std::string type) override;
  void SetFrame(int frame);
  void SetCameraFollower(bool cameraFollower);
};
