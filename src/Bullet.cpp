#include <Bullet.h>
#include <SpriteRenderer.h>
#include <Game.h>
#include <Collider.h>
#include <Character.h>
#include <Game.h>
#include <constants.h>

Bullet::Bullet(
  GameObject& associated,
  float angle,
  float speed,
  int damage,
  float maxDistance,
  bool targetsPlayer
) :
  Component(associated),
  speed(Vec2(speed, 0).Rotate(angle)),
  distanceLeft(maxDistance),
  damage(damage),
  targetsPlayer(targetsPlayer) {
  SpriteRenderer* sr = new SpriteRenderer(associated, BULLET_PATH, 1, 1);
  associated.AddComponent(sr);

  associated.angleDeg = angle * 180 / M_PI + 90;
}

Bullet::~Bullet() {}

void Bullet::Start() {
  Collider* collider = new Collider(associated);
  associated.AddComponent(collider);
}

void Bullet::Update(float dt) {
  associated.box.Move(speed * dt);
  distanceLeft -= speed.Magnitude() * dt;

  if (distanceLeft <= 0) {
    associated.RequestDelete();
  }
}

void Bullet::Render() {}

bool Bullet::Is(std::string type) {
  return type == "Bullet";
}

int Bullet::GetDamage() {
  return damage;
}

void Bullet::NotifyCollision(GameObject& other) {
  if (other.GetComponent("Zombie")) {
    associated.RequestDelete();
  }

  if (other.GetComponent("Character")) {
    Character* character = static_cast<Character*>(other.GetComponent("Character"));
    if ((targetsPlayer && Character::player == character) || (!targetsPlayer && Character::player != character)) {
      associated.RequestDelete();
    }
  }
}
