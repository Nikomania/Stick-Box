#pragma once

#include <DataStructure/Component.h>
#include <DataStructure/Animation.h>
#include <unordered_map>

class Animator: public Component {
private:
  std::unordered_map<std::string, Animation> animations;
  std::string current;
  int frameStart;
  int frameEnd;
  float frameTime;
  int currentFrame;
  float timeElapsed;
public:
  Animator(GameObject& associated);
  ~Animator();
  void Start() override;
  void Update(float dt) override;
  void Render() override;
  bool Is(std::string type) override;
  void SetAnimation(std::string name);
  void AddAnimation(std::string name, Animation anim);
};
