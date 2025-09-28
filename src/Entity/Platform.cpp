#include <Entity/Platform.h>
#include <Entity/Character.h>
#include <Manager/SpriteRenderer.h>
#include <DataStructure/constants.h>
#include <Physics/Collider.h>
#include <iostream>

Platform::Platform(GameObject& associated) :
Component(associated),
playerOnTop(false),
notifiedCollision(false) {
  // SpriteRenderer* spriteRenderer = new SpriteRenderer(
  //   associated,
  //   sprite,
  //   CHARACTER_frameCountW,
  //   CHARACTER_frameCountH
  // );
  // spriteRenderer->SetScale(4, 4);
  // associated.AddComponent(spriteRenderer);
}

Platform::~Platform() {}

void Platform::Start() {
  Collider* collider = new Collider(associated, {1, 1}, {0, 0});
  associated.AddComponent(collider);
}

void Platform::Update(float dt) {
  if (!notifiedCollision) {
    playerOnTop = false;
  }

  std::cout << "Player " << (playerOnTop ? "" : "not ") << "on top of platform\n";

  notifiedCollision = false;
}

void Platform::Render() {}

bool Platform::Is(std::string type) {
  return type == "Platform";
}

void Platform::NotifyCollision(GameObject& other, Vec2 MTV) {
  if (other.GetComponent("Character")) {
    Character* character = static_cast<Character*>(other.GetComponent("Character"));
    if (character == Character::player && MTV.y < 0) {
      playerOnTop = true;
      notifiedCollision = true;
    }
  }
}
