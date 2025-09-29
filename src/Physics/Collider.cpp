#include <Physics/Collider.h>
#include <DataStructure/constants.h>
#include <cmath>

#ifdef DEBUG
#include <HUD/Camera.h>
#include <Core/Game.h>

#include <SDL2/SDL.h>
#endif // DEBUG

Collider::Collider(
	GameObject& associated,
	Vec2 scale,
	Vec2 offset,
	bool isStatic,
	float gravity,
	float maxVelocity
):
Component(associated),
scale(scale),
offset(offset),
box(),
speed(),
gravity(gravity),
isStatic(isStatic),
maxVelocity(maxVelocity),
accelerations() {}

void Collider::Start() {
	accelerations["gravity"] = Vec2(0, gravity);
}

void Collider::Update(float dt) {
	if (!isStatic) {
		for (
			auto accel_it = accelerations.begin();
			accel_it != accelerations.end();
			++accel_it
		) {
			speed += accel_it->second * dt;
		}
		if (speed.Magnitude() > maxVelocity && maxVelocity != -1) {
			speed = speed.Normalize() * maxVelocity;
		}

		associated.box.Move(speed * dt);
	}
	
	// this component (collider) is always updated after its mainComponent
	// onGround will have the correct value from NotifyCollision
	onGround = false;
	UpdateBox();
}

bool Collider::Is(std::string type) {
  return type == "Collider";
}

void Collider::SetScale(Vec2 scale) {
  this->scale = scale;
}

void Collider::SetOffset(Vec2 offset) {
  this->offset = offset;
}

void Collider::Render() {
#ifdef DEBUG
	Vec2 center( box.GetCenter() );
	SDL_Point points[5];

	Vec2 point = (Vec2(box.x, box.y) - center).Rotate( associated.angleDeg/(180/M_PI) )
					+ center - Camera::pos;
	points[0] = {(int)point.x, (int)point.y};
	points[4] = {(int)point.x, (int)point.y};
	
	point = (Vec2(box.x + box.w, box.y) - center).Rotate( associated.angleDeg/(180/M_PI) )
					+ center - Camera::pos;
	points[1] = {(int)point.x, (int)point.y};
	
	point = (Vec2(box.x + box.w, box.y + box.h) - center).Rotate( associated.angleDeg/(180/M_PI) )
					+ center - Camera::pos;
	points[2] = {(int)point.x, (int)point.y};
	
	point = (Vec2(box.x, box.y + box.h) - center).Rotate( associated.angleDeg/(180/M_PI) )
					+ center - Camera::pos;
	points[3] = {(int)point.x, (int)point.y};

	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
#endif // DEBUG
}

void Collider::NotifyCollision(GameObject& other, Vec2 MTV) {
	if (isStatic) return;

	onGround = MTV.y < 0 && static_cast<Collider*>(other.GetComponent("Collider"))->IsStatic();
	associated.box.Move(MTV);
	if (MTV.x != 0) speed.x = 0;
	if (MTV.y != 0) speed.y = 0;
	UpdateBox();
}

void Collider::UpdateBox() {
	box.w = associated.box.w * scale.x;
	box.h = associated.box.h * scale.y;
	box.SetCenter(associated.box.GetCenter() + offset);
}

Vec2 Collider::RemoveAcceleration(std::string id) {
	Vec2 removed = accelerations[id];
	accelerations.erase(id);
	return removed;
}

void Collider::SetMaxVelocity(float maxVelocity) {
	this->maxVelocity = maxVelocity <= 0 ? -1 : maxVelocity;
}

void Collider::AddSpeed(Vec2 deltaSpeed) {
	speed += deltaSpeed;
	if (speed.Magnitude() > maxVelocity && maxVelocity != -1) {
		speed = speed.Normalize() * maxVelocity;
	}
}
