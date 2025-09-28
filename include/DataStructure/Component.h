#pragma once
#include <iostream>
#include <Physics/Vec2.h>
#include <string>


class GameObject;

class Component {
protected:
  GameObject& associated;
public:
  Component(GameObject& associated);
  virtual ~Component();
  
  virtual void Start() = 0;
  virtual void Update(float dt) = 0;
  virtual void Render() = 0;
  virtual bool Is(std::string type) = 0;

  virtual void NotifyCollision(GameObject& other, Vec2 MTV);
};
