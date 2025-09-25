#pragma once

#include <DataStructure/Component.h>
#include <Core/GameObject.h>
#include <Physics/Vec2.h>
#include <Utils/Timer.h>
#include <Resource/Sound.h>
#include <DataStructure/constants.h>
#include <memory>
#include <queue>

const Rect ALLOWED_BOX(BORDER_POS_X, BORDER_POS_Y, DEFAULT_MAP_WIDTH, DEFAULT_MAP_HEIGHT);

class Character: public Component {
public:
  Character(GameObject& associated, std::string sprite, int hp=CHARACTER_HP);
  ~Character();
  
  void Start() override;
  void Update(float dt) override;
  void Render() override;
  bool Is(std::string type) override;
  void NotifyCollision(GameObject& other) override;

  class Command {
    public:
      enum CommandType {Move, Shoot, Reload};
      CommandType type;
      Vec2 pos;
      Command(CommandType type, float x, float y);
  };

  void Issue(Command task);
  void Damage(int damage);

  static Character* player;
  bool godMode;
private:
  std::weak_ptr<GameObject> gun;
  std::queue<Command> taskQueue;
  Vec2 speed;
  float linearSpeed;

  int hp;
  bool hit;
  bool dead;

  Sound deathSound;
  Sound damageSound;

  Timer deathTimer;
  Timer hitTimer;
};
