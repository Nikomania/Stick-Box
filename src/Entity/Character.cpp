#include <Entity/Character.h>
#include <Manager/SpriteRenderer.h>
#include <Manager/Animator.h>
#include <DataStructure/Animation.h>
#include <Manager/InputManager.h>
#include <Core/Game.h>
#include <Physics/Collider.h>
#include <HUD/Camera.h>
#include <Physics/Gravity.h>
#include <Entity/Platform.h>
#include <Physics/Collision.h>
#include <Physics/RigidBody.h>

Character* Character::player = nullptr;

Character::Character(GameObject& associated, std::string sprite, int hp) :
  Component(associated),
  hp(hp),
  speed(0, 0),
  linearSpeed(CHARACTER_SPEED),
  deathTimer(),
  hitTimer(),
  dead(false),
  hit(false),
  damageSound(CHARACTER_DAMAGE_SOUND),
  deathSound(CHARACTER_DEATH_SOUND),
  facingRight(true),
  godMode(false) {
  SpriteRenderer* spriteRenderer = new SpriteRenderer(
    associated,
    sprite,
    CHARACTER_frameCountW,
    CHARACTER_frameCountH
  );
  spriteRenderer->SetScale(4, 4);
  associated.AddComponent(spriteRenderer);

  Animator* animator = new Animator(associated);
  animator->AddAnimation("walk", Animation(2, 6, CHARACTER_WALK_FRAME_TIME));
  animator->AddAnimation(
    "walk-left",
    Animation(2, 6, CHARACTER_WALK_FRAME_TIME, SDL_FLIP_HORIZONTAL)
  );
  animator->AddAnimation("idle", Animation(0, 1, CHARACTER_IDLE_FRAME_TIME));
  animator->AddAnimation("idle-left", Animation(0, 1, CHARACTER_IDLE_FRAME_TIME, SDL_FLIP_HORIZONTAL));
  animator->AddAnimation("death", Animation(0, 0, CHARACTER_DEATH_FRAME_TIME));
  animator->SetAnimation("idle");
  associated.AddComponent(animator);

  Gravity* gravity = new Gravity(associated, GRAVITY);
  associated.AddComponent(gravity);

  RigidBody* rigidBody = new RigidBody(associated);
  associated.AddComponent(rigidBody);
}

Character::~Character() {
  if (player == this) {
    player = nullptr;
  }
}

void Character::Start() {
  Collider* collider = new Collider(associated, {0.65, 0.9}, {0, 2});
  associated.AddComponent(collider);
}

void Character::Update(float dt) {
  hitTimer.Update(dt);
  deathTimer.Update(dt);

  if (dead) {
    if (deathTimer.Get() > CHARACTER_DEATH_TIME) {
      if (Character::player == this) {
        Camera::Unfollow();
      }
      associated.RequestDelete();
    }
    return;
  }

  InputManager& input = InputManager::GetInstance();

  bool moving = false;
  while (!taskQueue.empty()) {
    auto command = taskQueue.front();

    if (command.type == Command::CommandType::Move) {
      Vec2 movement_dir = (command.pos).Normalize();
      speed = movement_dir * linearSpeed;

      associated.box.Move(speed * dt);
      moving = true;
    }

    taskQueue.pop();
  }

  Component* animatorComponent = associated.GetComponent("Animator");
  if (animatorComponent == nullptr) {
    std::cout << "Error: No animator component found" << std::endl;
    exit(1);
  }
  Animator* animator = static_cast<Animator*>(animatorComponent);

  if (moving) {
    if (speed.x > 0) {
      facingRight = true;
      animator->SetAnimation("walk");
    } else if (speed.x < 0) {
      facingRight = false;
      animator->SetAnimation("walk-left");
    }
  } else {
    animator->SetAnimation(facingRight ? "idle": "idle-left");
    speed = Vec2(0, 0);
  }
}

void Character::Render() {}

bool Character::Is(std::string type) {
  return type == "Character";
}

void Character::Issue(Command task) {
  taskQueue.push(task);
}

void Character::Damage(int damage) {
  bool isMainChar = Character::player == this;
  if (dead || hitTimer.Get() < CHARACTER_HIT_TIME || (godMode && isMainChar)) {
    return;
  }

  hp -= damage;
  std::cout << (isMainChar ? "main ": "") << "character damage: " << damage <<" / current hp: " << hp << std::endl;

  if (hp <= 0) {
    Component* comp_anim = associated.GetComponent("Animator");

    if (comp_anim == nullptr) {
      std::cout << "Error: Animator not found in Character\n";
      exit(1);
    }
    Animator* animator = static_cast<Animator*>(comp_anim);
    animator->SetAnimation("death");
    deathSound.Play(1);

    associated.RemoveComponent(associated.GetComponent("Collider"));

    dead = true;
    hit = false;
    deathTimer.Restart();
    std::cout << (isMainChar ? "main ": "") << " character died\n";
    return;
  }

  damageSound.Play(1);

  hit = true;
  hitTimer.Restart();
}

Character::Command::Command(CommandType type, float x, float y) :
  type(type),
  pos(x, y) {}

void Character::NotifyCollision(GameObject& other) {}
