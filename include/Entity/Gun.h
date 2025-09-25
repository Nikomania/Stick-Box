#pragma once

#include <DataStructure/Component.h>
#include <Core/GameObject.h>
#include <Resource/Sound.h>
#include <Utils/Timer.h>
#include <Physics/Vec2.h>
#include <DataStructure/constants.h>
#include <memory>

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
