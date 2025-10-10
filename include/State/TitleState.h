#pragma once
#include <DataStructure/State.h>

class TitleState: public State {
public:
  TitleState();

  void LoadAssets() override;
  void Update(float dt) override;
  void Render() override;

  void Start() override;
  void Pause() override;
  void Resume() override;
};
