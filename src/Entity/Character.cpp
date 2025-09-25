#include <Entity/Character.h>
#include <Manager/SpriteRenderer.h>
#include <Manager/Animator.h>
#include <DataStructure/Animation.h>
#include <Entity/Gun.h>
#include <Manager/InputManager.h>
#include <Core/Game.h>
#include <Physics/Collider.h>
#include <HUD/Camera.h>
#include <Entity/Bullet.h>

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
  godMode(false) {
  SpriteRenderer* spriteRenderer = new SpriteRenderer(
    associated,
    sprite,
    CHARACTER_frameCountW,
    CHARACTER_frameCountH
  );
  associated.AddComponent(spriteRenderer);

  Animator* animator = new Animator(associated);
  animator->AddAnimation("walk", Animation(0, 5, CHARACTER_FRAME_TIME));
  animator->AddAnimation(
    "walk-left",
    Animation(0, 5, CHARACTER_FRAME_TIME, SDL_FLIP_HORIZONTAL)
  );
  animator->AddAnimation("idle", Animation(6, 9, CHARACTER_FRAME_TIME));
  animator->AddAnimation("death", Animation(10, 11, CHARACTER_FRAME_TIME));
  animator->SetAnimation("idle");
  associated.AddComponent(animator);
}

Character::~Character() {
  if (player == this) {
    player = nullptr;
  }
}

void Character::Start() {
  GameObject* gunGO = new GameObject();
  std::weak_ptr<GameObject> associatedWeakPtr(
    Game::GetInstance().GetCurrentState().GetObjectPtr(&associated)
  );
  Gun* gunComponent = new Gun(*gunGO, associatedWeakPtr);
  gunGO->AddComponent(gunComponent);
  Game::GetInstance().GetCurrentState().AddObject(gunGO);

  gun = Game::GetInstance().GetCurrentState().GetObjectPtr(gunGO);

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

      // Allow player to only move inside the map
      if (
        ALLOWED_BOX.Contains(
          (speed * dt) + associated.box.GetPos() + Camera::pos
        ) ||
        player != this
      ) {
        associated.box.Move(speed * dt);
        moving = true;
      }
      else {
        speed = Vec2(0, 0);
        moving = false;
      }
    } else if (command.type == Command::CommandType::Shoot) {
      std::shared_ptr<GameObject> gunPtr = gun.lock();
      Component* component = gunPtr->GetComponent("Gun");
      if (component == nullptr) {
        std::cout << "Error: No gun component found" << std::endl;
        exit(1);
      }
      Gun *gunComponent = static_cast<Gun *>(component);
      if (gunComponent->GetBulletCount() > 0) {
        gunComponent->Shoot(command.pos);
      } else {
        gunComponent->Reload();
      }
    } else if (command.type == Command::CommandType::Reload) {
      std::shared_ptr<GameObject> gunPtr = gun.lock();
      Component* component = gunPtr->GetComponent("Gun");
      if (component == nullptr) {
        std::cout << "Error: No gun component found" << std::endl;
        exit(1);
      }
      Gun *gunComponent = static_cast<Gun *>(component);  
      gunComponent->Reload();
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
    if (speed.x >= 0) {
      animator->SetAnimation("walk");
    } else {
      animator->SetAnimation("walk-left");
    }
  } else {
    animator->SetAnimation("idle");
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

    std::shared_ptr<GameObject> gunGO = gun.lock();
    gunGO->RequestDelete();
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

void Character::NotifyCollision(GameObject& other) {
  if (other.GetComponent("Bullet")) {
    Bullet* bullet = static_cast<Bullet*>(other.GetComponent("Bullet"));
    if (bullet->targetsPlayer && Character::player == this || !bullet->targetsPlayer && Character::player != this) {
      Damage(BULLET_DAMAGE);
    }
    return;
  }
}
