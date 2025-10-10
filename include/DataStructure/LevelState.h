#pragma once

#include <DataStructure/State.h>
#include <memory>
#include <unordered_map>

class LevelState: public State {
public:
  typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT
  } exit_t;

  LevelState(exit_t playerEntrance=LEFT);
  ~LevelState() override;
protected:
  std::unordered_map<exit_t, std::unique_ptr<State>> exits;
  exit_t playerEntrance;
};
