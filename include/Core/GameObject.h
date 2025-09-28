#pragma once
#include <Physics/Rect.h>
#include <DataStructure/Component.h>
#include <Physics/Vec2.h>
#include <iostream>
#include <vector>

class GameObject {
private:
  std::vector<Component*> components;
  bool isDead;
  bool started;
public:
  GameObject();
  ~GameObject();

  void Update(float dt);
  void Render();
  void Start();

  bool IsDead();
  void RequestDelete();

  void AddComponent(Component* cpt);
  void RemoveComponent(Component* cpt);
  Component* GetComponent(std::string type);

  static int Compare(const void * a, const void * b);

  void NotifyCollision(GameObject& other, Vec2 MTV);

  Rect box;
  double angleDeg;
};
