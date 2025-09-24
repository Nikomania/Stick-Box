#include <TitleState.h>
#include <GameObject.h>
#include <SpriteRenderer.h>
#include <InputManager.h>
#include <StateStage.h>
#include <Game.h>
#include <Text.h>
#include <constants.h>

TitleState::TitleState() : State() {}

TitleState::~TitleState() {
  objectArray.clear();
}

void TitleState::LoadAssets() {
  GameObject* titleGO = new GameObject();
  SpriteRenderer* titleSR = new SpriteRenderer(*titleGO, TITLE_IMAGE_PATH, 1, 1);
  titleSR->SetCameraFollower(true);
  titleGO->AddComponent(titleSR);
  AddObject(titleGO);

  GameObject* pressSpaceGO = new GameObject();
  Text* pressSpaceText = new Text(
    *pressSpaceGO,
    DEFAULT_FONT_PATH,
    DEFAULT_FONT_SIZE,
    Text::TextStyle::SOLID,
    TITLE_MESSAGE,
    WHITE,
    BLACK,
    true,
    BLINK_SHOW_TIME,
    BLINK_HIDDEN_TIME
  );
  pressSpaceGO->box.SetCenter(
    Vec2(
      DEFAULT_SCREEN_WIDTH / 2,
      DEFAULT_SCREEN_HEIGHT - 100
    )
  );
  pressSpaceText->SetCameraFollower(true);
  pressSpaceGO->AddComponent(pressSpaceText);
  AddObject(pressSpaceGO);
}

void TitleState::Update(float dt) {
  InputManager& input = InputManager::GetInstance();
  if (input.KeyPress(ESCAPE_KEY) || input.QuitRequested()) {
    quitRequested = true;
  }

  if (input.KeyPress(SPACE_BAR)) {
    Game::GetInstance().Push(new StateStage());
  }

  UpdateArray(dt);
}

void TitleState::Render() {
  RenderArray();
}

void TitleState::Start() {
  if (!started) {
    LoadAssets();
    StartArray();
    started = true;
  }
}

void TitleState::Pause() {}

void TitleState::Resume() {}
