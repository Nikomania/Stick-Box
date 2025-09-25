#include <DataStructure/Component.h>
#include <Core/GameObject.h>

Component::Component(GameObject& associated) : associated(associated) {}

Component::~Component() {}

void Component::NotifyCollision(GameObject& other) {}
