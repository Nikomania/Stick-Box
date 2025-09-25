#pragma once

#include <DataStructure/State.h>
#include <Core/GameObject.h>
#include <Resource/Music.h>
#include <Level/TileSet.h>

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
