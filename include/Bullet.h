#pragma once
#include <Component.h>
#include <GameObject.h>
#include <Vec2.h>

class Bullet: public Component {
public:
  Bullet(
    GameObject& associated,
    float angle,
    float speed,
    int damage,
    float maxDistance,
    bool targetsPlayer
  );
  ~Bullet();
  
  void Start() override;
  void Update(float dt) override;
  void Render() override;
  bool Is(std::string type) override;
  void NotifyCollision(GameObject& other) override;

  int GetDamage();

  bool targetsPlayer;
private:
  Vec2 speed;
  float distanceLeft;
  int damage;
};
