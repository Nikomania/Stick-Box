#include <Physics/RigidBody.h>
#include <Physics/Collision.h>
#include <Physics/Gravity.h>


RigidBody::RigidBody(GameObject& associated) :
Component(associated),
MTV(Vec2()),
isColliding(false) {}

RigidBody::~RigidBody() {}

void RigidBody::Start() {}

void RigidBody::Update(float dt) {
  if (isColliding) {
    associated.box.Move(MTV);
    isColliding = false;
  }
}

void RigidBody::Render() {}

bool RigidBody::Is(std::string type) {
  return type == "RigidBody";
}

void RigidBody::NotifyCollision(GameObject& other, Vec2 MTV) {
  this->MTV = MTV;
  isColliding = true;
}
