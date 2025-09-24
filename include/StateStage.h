#pragma once

#include <State.h>
#include <GameObject.h>
#include <Music.h>
#include <TileSet.h>

class StateStage: public State {
public:
  StateStage();
  ~StateStage() override;

  void LoadAssets() override;
  void Update(float dt) override;
  void Render() override;

  void Start() override;
  void Pause() override;
  void Resume() override;
private:
  Music backgroundMusic;
  TileSet* tileSet;
};
