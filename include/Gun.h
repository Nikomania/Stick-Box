#pragma once

#include <Component.h>
#include <GameObject.h>
#include <Sound.h>
#include <Timer.h>
#include <Vec2.h>
#include <memory>
#include <constants.h>

class Gun: public Component {
public:
  Gun(
    GameObject& associated,
    std::weak_ptr<GameObject> character,
    int maxBulletCount=BULLET_COUNT_DEFAULT
  );
  ~Gun();
  
  void Start() override;
  void Update(float dt) override;
  void Render() override;
  bool Is(std::string type) override;
  void Shoot(Vec2 target);
  void Reload();
  int GetBulletCount();
private:
  void GenerateBullets(Vec2 target);

  Sound shotSound;
  Sound reloadSound;
  int cooldown;
  Timer cdTimer;
  std::weak_ptr<GameObject> character;
  float angle;
  int bulletCount;
  const int maxBulletCount;
};
