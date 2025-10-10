#pragma once

#include <DataStructure/LevelState.h>
#include <Core/GameObject.h>
#include <Resource/Music.h>
#include <Level/TileSet.h>

class CloseCombatState: public LevelState {
public:
  CloseCombatState(exit_t playerEntrance=LEFT);

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
