#pragma once
#include <State.h>

class TitleState: public State {
public:
  TitleState();
  ~TitleState() override;

  void LoadAssets() override;
  void Update(float dt) override;
  void Render() override;

  void Start() override;
  void Pause() override;
  void Resume() override;
};
