#include <SDL2/SDL.h>
#include <Zombie.h>
#include <SpriteRenderer.h>
#include <Animation.h>
#include <Animator.h>
#include <InputManager.h>
#include <Camera.h>
#include <Collider.h>
#include <Character.h>
#include <Game.h>
#include <constants.h>
#include <iostream>

int Zombie::zombieCount = 0;

Zombie::Zombie(GameObject& associated, int hitpoints) : 
  Component(associated), 
  hit(false),
  dead(false),
  hitpoints(hitpoints),
  hitTimer(),
  deathSound(ZOMBIE_DEATH_SOUND),
  damageSound(ZOMBIE_DAMAGE_SOUND) {
  SpriteRenderer* sr = new SpriteRenderer(associated, ZOMBIE_PATH, ZOMBIE_frameCountW, ZOMBIE_frameCountH);
  associated.AddComponent(sr);

  Animator* animator = new Animator(associated);
  animator->AddAnimation("walk", Animation(0, 3, ZOMBIE_FRAME_TIME));
  animator->AddAnimation("walk-left", Animation(0, 3, ZOMBIE_FRAME_TIME, SDL_FLIP_HORIZONTAL));
  animator->AddAnimation("hit", Animation(4, 4, 0));
  animator->AddAnimation("hit-left", Animation(4, 4, 0, SDL_FLIP_HORIZONTAL));
  animator->AddAnimation("death", Animation(5, 5, 0));
  animator->SetAnimation("walk");
  associated.AddComponent(animator);

  Zombie::zombieCount++;
  SDL_Log("Zombie created!\n");
}

Zombie::~Zombie() {
  Zombie::zombieCount--;
}

void Zombie::Damage(int damage) {
  if (dead || hitTimer.Get() < ZOMBIE_HIT_TIME) {
    return;
  }

  hitpoints -= damage;
  std::cout << "zombie damage: " << damage << " / hp: " << hitpoints << std::endl;

  Component* comp_anim = associated.GetComponent("Animator");
  Animator* animator = static_cast<Animator*>(comp_anim);

  if (comp_anim == nullptr) {
    std::cout << "Error: Animator not found in Zombie\n";
    exit(1);
  }

  if (hitpoints <= 0) {
    animator->SetAnimation("death");
    deathSound.Play(1);

    associated.RemoveComponent(associated.GetComponent("Collider"));

    dead = true;
    hit = false;
    deathTimer.Restart();
    std::cout << "zombie dead\n";
    return;
  }

  animator->SetAnimation("hit");
  damageSound.Play(1);

  hit = true;
  hitTimer.Restart();
}

void Zombie::Start() {
  Collider *collider = new Collider(associated, {0.65, 0.9}, {0, 0});
  associated.AddComponent(collider);
}

void Zombie::Update(float dt) {
  hitTimer.Update(dt);
  deathTimer.Update(dt);

  if (dead) {
    if (deathTimer.Get() > ZOMBIE_DEATH_TIME) {
      associated.RequestDelete();
    }
    return;
  }

  Vec2 speed_dir = {0, 0};
  if (Character::player != nullptr) {
    Vec2 playerCenterPos = Rect(
      Camera::pos.x,
      Camera::pos.y,
      DEFAULT_SCREEN_WIDTH,
      DEFAULT_SCREEN_HEIGHT
    ).GetCenter();
    Vec2 zombiePos = associated.box.GetCenter();
    speed_dir = (playerCenterPos - zombiePos).Normalize();
    Vec2 speed = speed_dir * ZOMBIE_SPEED;
    associated.box.Move(speed * dt);
  }

  if (hit && hitTimer.Get() > ZOMBIE_HIT_TIME) {
    hit = false;
  }

  Component* comp_anim = associated.GetComponent("Animator");
  if (comp_anim == nullptr) {
    std::cout << "Error: Animator not found in Zombie\n";
    exit(1);
  }
  Animator* animator = static_cast<Animator*>(comp_anim);

  if (hit) {
    animator->SetAnimation(speed_dir.x >= 0 ? "hit" : "hit-left");
  } else {
    animator->SetAnimation(speed_dir.x >= 0 ? "walk" : "walk-left");
  }
}

void Zombie::NotifyCollision(GameObject& other) {
  if (other.GetComponent("Bullet")) {
    Damage(BULLET_DAMAGE);
  }
}

void Zombie::Render() {}

bool Zombie::Is(std::string type) {
  return type == "Zombie";
}
