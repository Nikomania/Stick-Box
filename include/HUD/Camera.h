#pragma once
#include <Core/GameObject.h>
#include <Physics/Vec2.h>

class Camera {
private:
  static GameObject* focus;
public:
  static Vec2 pos;
  static Vec2 speed;

  void static Follow(GameObject* newFocus);
  void static Unfollow();
  void static Update(float dt);
};
