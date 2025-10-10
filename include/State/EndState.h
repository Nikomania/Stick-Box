#pragma once

#include <DataStructure/State.h>
#include <Resource/Music.h>

class EndState : public State {
public:
  EndState();

  void LoadAssets() override;
  void Update(float dt) override;
  void Render() override;

  void Start() override;
  void Pause() override;
  void Resume() override;
private:
  Music backgroundMusic;
};
