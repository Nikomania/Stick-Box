#pragma once

#include <DataStructure/Component.h>
#include <Core/GameObject.h>

class RigidBody : public Component {
public:
  RigidBody(GameObject& associated);
  ~RigidBody();

  void Start() override;
  void Update(float dt) override;
  void Render() override;
  bool Is(std::string type) override;

  void NotifyCollision(GameObject& other) override;
private:
  Vec2* collisionDirection = nullptr;
  bool isColliding = false;
};
