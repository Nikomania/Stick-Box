#include <Physics/RigidBody.h>
#include <Physics/Collision.h>


RigidBody::RigidBody(GameObject& associated) :
Component(associated), collisionDirection(nullptr), isColliding(false) {}

RigidBody::~RigidBody() {}

void RigidBody::Start() {}

void RigidBody::Update(float dt) {
  if (isColliding) {
    associated.box.Move(*collisionDirection * (-0.5) * dt);
    isColliding = false;
    delete collisionDirection;
    collisionDirection = nullptr;
  }
}

void RigidBody::Render() {}

bool RigidBody::Is(std::string type) {
  return type == "RigidBody";
}

void RigidBody::NotifyCollision(GameObject& other) {
  Vec2* newCollisionDirection = Collision::GetCollisionDirection(
    associated.box,
    other.box,
    associated.angleDeg * M_PI / 180,
    other.angleDeg * M_PI / 180
  );
  isColliding = newCollisionDirection != nullptr;
  if (isColliding) {
    collisionDirection = newCollisionDirection;
  }
}
