#pragma once

#include <DataStructure/Component.h>
#include <Core/GameObject.h>
#include <Physics/Vec2.h>
#include <Physics/Rect.h>
#include <iostream>
#include <map>
#include <string>
#include <tuple>

#define DEBUG

class Collider: public Component {
public:
  Collider(
    GameObject& associated,
    Vec2 scale = {1, 1},
    Vec2 offset = {0, 0},
    bool isStatic = true,
    float gravity = 0,
    float maxVelocity = -1
  );
  Rect box;
  Vec2 speed;

  void Start() override;
  void Update(float dt) override;
  void Render() override;
  bool Is(std::string type) override;

  void SetScale(Vec2 scale);
  void SetOffset(Vec2 offset);
  void SetMaxVelocity(float maxVelocity);
  void AddSpeed(Vec2 deltaSpeed);

  inline void InsertAcceleration(std::string id, Vec2 acceleration) {
    accelerations[id] = acceleration;
  }
  Vec2 RemoveAcceleration(std::string id);
  inline bool IsStatic() const { return isStatic; }
  inline bool IsOnGround() const { return onGround; }

  void NotifyCollision(GameObject& other, Vec2 MTV) override;
private:
  Vec2 scale;
  Vec2 offset;
  bool isStatic;
  float gravity;
  float maxVelocity;
  std::map<std::string, Vec2> accelerations;

  bool onGround;

  void UpdateBox();
};
