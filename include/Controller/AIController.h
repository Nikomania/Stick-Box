#pragma once

#include <DataStructure/Component.h>
#include <Core/GameObject.h>
#include <Utils/Timer.h>
#include <Physics/Vec2.h>
#include <iostream>

class AIController: public Component {
public:
  AIController(GameObject& associated);

  void Start() override;
  void Update(float dt) override;
  void Render() override;
  bool Is(std::string type) override;
private:
  int npcCounter;
  enum AIState {
    MOVING,
    RESTING
  };
  AIState state;
  Timer restTimer;
  Vec2 destination;
  int cooldownRest;
};
