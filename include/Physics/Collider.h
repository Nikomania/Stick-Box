#pragma once

#include <DataStructure/Component.h>
#include <Core/GameObject.h>
#include <Physics/Vec2.h>
#include <Physics/Rect.h>
#include <iostream>

class Collider: public Component {
public:
  Collider(GameObject& associated, Vec2 scale = {1, 1}, Vec2 offset = {0, 0});
  Rect box;

  void Start() override;
  void Update(float dt) override;
  void Render() override;
  bool Is(std::string type) override;

  void SetScale(Vec2 scale);
  void SetOffset(Vec2 offset);
private:
  Vec2 scale;
  Vec2 offset;
};
