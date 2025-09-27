#include <Controller/PlayerController.h>
#include <Manager/InputManager.h>
#include <Entity/Character.h>
#include <HUD/Camera.h>
#include <Core/Game.h>

PlayerController::PlayerController(GameObject& associated) : Component(associated) {}

PlayerController::~PlayerController() {}

void PlayerController::Start() {}

void PlayerController::Update(float dt) {
  InputManager& input = InputManager::GetInstance();
  Vec2 speed = Vec2(0, 0);
  
  if (input.IsKeyDown(W_KEY) || input.IsKeyDown(UP_ARROW_KEY)) {
    speed.y -= 1;
  }

  if (input.IsKeyDown(S_KEY) || input.IsKeyDown(DOWN_ARROW_KEY)) {
    speed.y += 1;
  }

  if (input.IsKeyDown(A_KEY) || input.IsKeyDown(LEFT_ARROW_KEY)) {
    speed.x -= 1;
  }

  if (input.IsKeyDown(D_KEY) || input.IsKeyDown(RIGHT_ARROW_KEY)) {
    speed.x += 1;
  }

  std::shared_ptr<GameObject> character_ptr = 
    Game::GetInstance().GetCurrentState().GetObjectPtr(&associated).lock();

  Character* character =
    static_cast<Character*>(character_ptr->GetComponent("Character"));

  if (speed.Magnitude() > 0) {
    character->Issue(
      Character::Command(
        Character::Command::CommandType::Move,
        speed.x,
        speed.y
      )
    );
  }
}

void PlayerController::Render() {}

bool PlayerController::Is(std::string type) {
  return type == "PlayerController";
}
