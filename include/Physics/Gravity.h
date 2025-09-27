#pragma once

#include <DataStructure/Component.h>
#include <Core/GameObject.h>

class Gravity : public Component {
public:
  Gravity(GameObject& associated, float g = 9.8);
  ~Gravity();

  void Start() override;
  void Update(float dt) override;
  void Render() override;
  bool Is(std::string type) override;

  void turnOff();
  void turnOn();
private:
  float g;
  bool active = true;
};
