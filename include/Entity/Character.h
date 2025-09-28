#pragma once

#include <DataStructure/Component.h>
#include <Core/GameObject.h>
#include <Physics/Vec2.h>
#include <Utils/Timer.h>
#include <Resource/Sound.h>
#include <DataStructure/constants.h>
#include <memory>
#include <queue>

class Character: public Component {
public:
  Character(GameObject& associated, std::string sprite, int hp=CHARACTER_HP);
  ~Character();
  
  void Start() override;
  void Update(float dt) override;
  void Render() override;
  bool Is(std::string type) override;
  void NotifyCollision(GameObject& other, Vec2 MTV) override;

  class Command {
    public:
      enum CommandType {Move};
      CommandType type;
      Vec2 pos;
      Command(CommandType type, float x, float y);
  };

  void Issue(Command task);
  void Damage(int damage);

  static Character* player;
  bool godMode;
private:
  std::queue<Command> taskQueue;
  Vec2 speed;
  float linearSpeed;
  bool facingRight;

  int hp;
  bool hit;
  bool dead;

  Sound deathSound;
  Sound damageSound;

  Timer deathTimer;
  Timer hitTimer;
};
