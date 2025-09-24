#include <AIController.h>
#include <Camera.h>
#include <Rect.h>
#include <Character.h>
#include <constants.h>

AIController::AIController(GameObject& associated) :
  Component(associated),
  npcCounter(0),
  state(RESTING),
  restTimer(),
  destination(),
  cooldownRest(COOLDOWN_REST) {
}

void AIController::Start() {}

void AIController::Update(float dt) {
  if (Character::player == nullptr) {
    return;
  }
  restTimer.Update(dt);

  Component* character_comp = associated.GetComponent("Character");
  if (character_comp == nullptr) {
    std::cout << "Error: No character component found in AIController\n";
    exit(1);
  }
  Character* character = static_cast<Character*>(character_comp);

  switch (state) {
  case RESTING:
    if (restTimer.Get() > cooldownRest) {
      state = MOVING;
      restTimer.Restart();
      destination = Rect(Camera::pos.x, Camera::pos.y, DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT).GetCenter();
    }
    break;
  case MOVING:
    if (associated.box.GetCenter().Distance(destination) <= AI_DISTANCE) {
      state = RESTING;
      Vec2 playerCenterPos = Rect(Camera::pos.x, Camera::pos.y, DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT).GetCenter();

      character->Issue(Character::Command(Character::Command::CommandType::Shoot, playerCenterPos.x, playerCenterPos.y));
      restTimer.Restart();
    } else {
      Vec2 move_dir = (destination - associated.box.GetCenter()).Normalize();
      character->Issue(Character::Command(Character::Command::CommandType::Move, move_dir.x, move_dir.y));
    }
    break;
  default:
    std::cout << "Error: AIController state not found (how?)\n";
    break;
  }
}

void AIController::Render() {}

bool AIController::Is(std::string type) {
  return type == "AIController";
}
