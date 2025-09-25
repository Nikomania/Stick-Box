#include <Entity/Gun.h>
#include <Manager/SpriteRenderer.h>
#include <Manager/Animator.h>
#include <Manager/InputManager.h>
#include <HUD/Camera.h>
#include <Entity/Character.h>
#include <Entity/Bullet.h>
#include <Core/Game.h>
#include <cmath>
#include <DataStructure/constants.h>

Gun::Gun(GameObject& associated, std::weak_ptr<GameObject> character, int maxBulletCount) :
  Component(associated),
  shotSound(GUN_SHOT_SOUND),
  reloadSound(GUN_RELOAD_SOUND),
  cooldown(GUN_COOLDOWN),
  cdTimer(),
  character(character),
  angle(0),
  maxBulletCount(maxBulletCount),
  bulletCount(maxBulletCount) {
  SpriteRenderer* sr = new SpriteRenderer(associated, GUN_PATH, GUN_FRAME_COUNT_W, GUN_FRAME_COUNT_H);
  associated.AddComponent(sr);

  Animator* animator = new Animator(associated);
  animator->AddAnimation("idle", Animation(0, 0, 0));
  animator->AddAnimation("idle-up-side-down", Animation(0, 0, 0, SDL_FLIP_VERTICAL));
  animator->AddAnimation("reload", Animation(1, 5, GUN_FRAME_TIME));
  animator->AddAnimation("reload-up-side-down", Animation(1, 5, GUN_FRAME_TIME, SDL_FLIP_VERTICAL));
  animator->SetAnimation("idle");
  associated.AddComponent(animator);

  std::shared_ptr<GameObject> character_shr = character.lock();
  Vec2 characterPos = character_shr->box.GetCenter();
  associated.box.SetCenter(characterPos + Vec2(GUN_CHARACTER_OFFSET, 0));

  cdTimer.Restart();
}

Gun::~Gun() {}

void Gun::Start() {}

void Gun::Update(float dt) {
  if (character.expired()) {
    associated.RequestDelete();
    return;
  }

  cdTimer.Update(dt);

  InputManager& input = InputManager::GetInstance();

  std::shared_ptr<GameObject> character_shr = character.lock();
  bool isMainCharacter = character_shr->GetComponent("Character") == Character::player;
  bool cooldownReady = cdTimer.Get() > cooldown;

  Vec2 characterCenter = character_shr->box.GetCenter();
  Vec2 mousePos = Vec2(input.GetMouseX(), input.GetMouseY());
  Vec2 offsetVector_dir = Vec2(1, 0);
  if (cooldownReady) {
    if (isMainCharacter) {
      offsetVector_dir = (mousePos + Camera::pos - characterCenter).Normalize();
    } else if (Character::player != nullptr) {
      Vec2 playerCenterPos = Rect(Camera::pos.x, Camera::pos.y, DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT).GetCenter();
      offsetVector_dir = (playerCenterPos - characterCenter).Normalize();
    }
    associated.angleDeg = offsetVector_dir.HorAngle() * 180 / M_PI;
    angle = associated.angleDeg * M_PI / 180;
  } else {
    offsetVector_dir = Vec2(1, 0).Rotate(angle);
  }
  associated.box.SetCenter(characterCenter + offsetVector_dir * GUN_CHARACTER_OFFSET);

  if (cooldownReady) {
    Animator* animator = static_cast<Animator*>(associated.GetComponent("Animator"));
    if (!animator) {
      std::cout << "Error: No animator component found" << std::endl;
      exit(1);
    }
    
    if (cos(angle) > 0) {
      animator->SetAnimation("idle");
    } else {
      animator->SetAnimation("idle-up-side-down");
    }
  }
}

void Gun::Render() {}

bool Gun::Is(std::string type) {
  return type == "Gun";
}

void Gun::Shoot(Vec2 target) {
  if (cdTimer.Get() < cooldown) {
    return;
  }

  GenerateBullets(target);

  shotSound.Play(1);
  cdTimer.Restart();
  std::cout << "Bang!" << std::endl;
}

void Gun::GenerateBullets(Vec2 target) {
  std::shared_ptr<GameObject> character_shr = character.lock();
  Vec2 characterCenter = character_shr->box.GetCenter();
  angle = (target - characterCenter).Normalize().HorAngle();

  Vec2 gunCenter = associated.box.GetCenter();
  Vec2 offsetVector_dir = Vec2(1, 0).Rotate(angle);
  Vec2 gunMuzzleCenter = gunCenter + (offsetVector_dir * associated.box.w / 2);

  float angles[] = {angle, angle + GUN_BULLET_ANGLE, angle - GUN_BULLET_ANGLE};

  Component *characterComp = character.lock()->GetComponent("Character");

  if (characterComp == nullptr) {
    std::cout << "There is no Character component in Gun's character attribute\n";
    exit(1);
  }

  Character *characterPtr = static_cast<Character *>(characterComp);

  for (float angle_bullet : angles) {
    GameObject* bulletGO = new GameObject();
    Bullet* bullet = new Bullet(
      *bulletGO,
      angle_bullet,
      BULLET_SPEED,
      BULLET_DAMAGE,
      BULLET_MAX_DISTANCE,
      Character::player != characterPtr
    );
    bulletGO->box.SetCenter(gunMuzzleCenter);
    bulletGO->AddComponent(bullet);
    Game::GetInstance().GetCurrentState().AddObject(bulletGO);
    bulletCount--;
    if (bulletCount <= 0) {
      return;
    }
  }
}

void Gun::Reload() {
  if (cdTimer.Get() < cooldown) {
    return;
  }

  Animator* animator = static_cast<Animator*>(associated.GetComponent("Animator"));
  if (!animator) {
    std::cout << "Error: No animator component found" << std::endl;
    exit(1);
  }
  
  if (cos(angle) > 0) {
    animator->SetAnimation("reload");
  } else {
    animator->SetAnimation("reload-up-side-down");
  }

  bulletCount = maxBulletCount;

  reloadSound.Play(1);
  cdTimer.Restart();
  std::cout << "Reloading..." << std::endl;
}

int Gun::GetBulletCount() {
  return bulletCount;
}
