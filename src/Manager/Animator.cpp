#include <Manager/Animator.h>
#include <Core/GameObject.h>
#include <DataStructure/Component.h>
#include <Manager/SpriteRenderer.h>
#include <iostream>

Animator::Animator(GameObject& associated) : Component(associated), animations() {
  current = "";
  frameStart = 0;
  frameEnd = 0;
  frameTime = 0;
  currentFrame = 0;
  timeElapsed = 0;
}

Animator::~Animator() {}

void Animator::Start() {}

void Animator::Update(float dt) {
  if (frameTime > 0) {
    timeElapsed += dt;
  }
  if (timeElapsed > frameTime) {
    currentFrame++;
    timeElapsed -= frameTime;

    if (currentFrame > frameEnd) {
      currentFrame = frameStart;
    }
  }

  static_cast<SpriteRenderer*>(
    associated.GetComponent("SpriteRenderer")
  )->SetFrame(
      currentFrame,
      animations[current].flip
  );
}

void Animator::Render() {}

bool Animator::Is(std::string type) {
  return type == "Animator";
}

void Animator::SetAnimation(std::string name) {
  if (current == name) {
    return;
  }

  auto anim_map_item = animations.find(name);
  if (anim_map_item == animations.end()) {
    std::cout << "Error: Couldn't set animation " << name << "\n";
    exit(1);
  }
  Animation anim = anim_map_item->second;

  frameStart = anim.frameStart;
  frameEnd = anim.frameEnd;
  frameTime = anim.frameTime;

  currentFrame = frameStart;
  timeElapsed = 0;

  static_cast<SpriteRenderer*>(
    associated.GetComponent("SpriteRenderer")
  )->SetFrame(
    currentFrame,
    animations[current].flip
  );
  current = name;
}

void Animator::AddAnimation(std::string name, Animation anim) {
  if (animations.find(name) == animations.end()) {
    animations[name] = anim;
  } else {
    std::cout << "Warning: Animation " << name << " already exists\n";
  }
}