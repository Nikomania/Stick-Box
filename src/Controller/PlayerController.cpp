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

  std::shared_ptr<GameObject> character_ptr = 
    Game::GetInstance().GetCurrentState().GetObjectPtr(&associated).lock();

  Character* character =
    static_cast<Character*>(character_ptr->GetComponent("Character"));

  if (input.IsKeyDown(SPACE_BAR)) {
    character->Issue(
      Character::Command(
        Character::Command::CommandType::Jump
      )
    );
  }

  if (input.IsKeyDown(A_KEY) || input.IsKeyDown(LEFT_ARROW_KEY)) {
    int* data = new int(-1);
    character->Issue(
      Character::Command(
        Character::Command::CommandType::Move, (void*) data
      )
    );
  }

  if (input.IsKeyDown(D_KEY) || input.IsKeyDown(RIGHT_ARROW_KEY)) {
    int* data = new int(1);
    character->Issue(
      Character::Command(
        Character::Command::CommandType::Move, (void*) data
      )
    );
  }
}

void PlayerController::Render() {}

bool PlayerController::Is(std::string type) {
  return type == "PlayerController";
}
