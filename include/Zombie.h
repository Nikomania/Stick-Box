#pragma once

#include <GameObject.h>
#include <Component.h>
#include <Sound.h>
#include <Timer.h>
#include <constants.h>

class Zombie: public Component {
private:
  Sound deathSound;
  Sound damageSound;
  Timer hitTimer;
  Timer deathTimer;

  int hitpoints;
  bool hit;
  bool dead;
public:
  Zombie(GameObject& associated, int hitpoints = ZOMBIE_HP);
  ~Zombie();

  void Damage(int damage);

  void Start() override;
  void Update(float dt) override;
  void Render() override;
  bool Is(std::string type) override;
  void NotifyCollision(GameObject& other) override;

  static int zombieCount;
};
