#include <GameObject.h>
#include <Component.h>
#include <memory>

GameObject::GameObject() : started(false), isDead(false), box(), angleDeg(0), components() {}

GameObject::~GameObject() {
  const int size = components.size();
  for (int i = size - 1; i >= 0; i--) {
    delete components[i];
  }
  components.clear();
}

void GameObject::Update(float dt) {
  const int size = components.size();
  for (int i = 0; i < size; i++) {
    components[i]->Update(dt);
  }
}

void GameObject::Render() {
  const int size = components.size();
  for (int i = 0; i < size; i++) {
    components[i]->Render();
  }
}

bool GameObject::IsDead() {
  return isDead;
}

void GameObject::RequestDelete() {
  isDead = true;
}

void GameObject::AddComponent(Component* cpt) {
  components.push_back(cpt);
  if (started) {
    cpt->Start();
  }
}

void GameObject::RemoveComponent(Component* cpt) {
  const int size = components.size();
  for (int i = 0; i < size; i++) {
    if (components[i] == cpt) {
      components.erase(components.begin() + i);
      return;
    }
  }
}

Component* GameObject::GetComponent(std::string type) {
  const int size = components.size();
  for (int i = 0; i < size; i++) {
    if (components[i]->Is(type)) {
      return components[i];
    }
  }
  return nullptr;
}

void GameObject::Start() {
  if (!started) {
    const int size = components.size();
    for (int i = 0; i < size; i++) {
      components[i]->Start();
    }

    started = true;
  }
}

int GameObject::Compare(const void * a, const void * b) {
  std::shared_ptr<GameObject> go1 = *(std::shared_ptr<GameObject>*)a;
  std::shared_ptr<GameObject> go2 = *(std::shared_ptr<GameObject>*)b;

  if (go1->box.y < go2->box.y)
    return -1;
  if (go1->box.y > go2->box.y)
    return 1;
  return 0;
}

void GameObject::NotifyCollision(GameObject& other) {
  const int size = components.size();
  for (int i = 0; i < size; i++) {
    components[i]->NotifyCollision(other);
  }
}
