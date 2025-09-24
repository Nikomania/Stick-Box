#pragma once

#include <Component.h>
#include <GameObject.h>

class PlayerController: public Component {
public:
  PlayerController(GameObject& associated);
  ~PlayerController();
  
  void Start() override;
  void Update(float dt) override;
  void Render() override;
  bool Is(std::string type) override;
};
