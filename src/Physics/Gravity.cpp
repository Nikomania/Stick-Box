#include <Physics/Gravity.h>
#include <math.h>

Gravity::Gravity(GameObject& associated, float g) : Component(associated), g(g) {}

Gravity::~Gravity() {}

void Gravity::Start() {}

void Gravity::Update(float dt) {
  if (!active) return;
  associated.box.Move(M_PI / 2, g * dt);
}

void Gravity::Render() {}

bool Gravity::Is(std::string type) {
  return type == "Gravity";
}

void Gravity::turnOff() {
  active = false;
}

void Gravity::turnOn() {
  active = true;
}
