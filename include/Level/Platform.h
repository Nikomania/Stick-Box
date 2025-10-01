#pragma once

#include <DataStructure/Component.h>
#include <Core/GameObject.h>

class Platform : public Component {
public:
  Platform(GameObject& associated);
  ~Platform();
  void Start() override;
  void Update(float dt) override;
  void Render() override;
  bool Is(std::string type) override;

  void NotifyCollision(GameObject& other, Vec2 MTV) override;
private:
  bool playerOnTop;
  bool notifiedCollision = false;
};
