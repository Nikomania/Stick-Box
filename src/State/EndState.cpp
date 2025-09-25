#include <State/EndState.h>
#include <DataStructure/GameData.h>
#include <Manager/InputManager.h>
#include <HUD/Camera.h>
#include <Manager/SpriteRenderer.h>
#include <Resource/Text.h>
#include <DataStructure/constants.h>

EndState::EndState() : State(), backgroundMusic() {
  SDL_Log("EndState created!\n");
}

EndState::~EndState() {
  objectArray.clear();
}

void EndState::LoadAssets() {
  GameObject* bgGO = new GameObject();
  SpriteRenderer* bgSprite = new SpriteRenderer(*bgGO);
  if (GameData::playerVictory) {
    bgSprite->Open(END_IMAGE_WIN_PATH);
    backgroundMusic.Open(MUSIC_PATH_WIN);
  } else {
    bgSprite->Open(END_IMAGE_LOSE_PATH);
    backgroundMusic.Open(MUSIC_PATH_LOSE);
  }
  SDL_Log("Music loaded!\n");
  bgSprite->SetCameraFollower(true);
  bgGO->AddComponent(bgSprite);
  AddObject(bgGO);

  GameObject* textQuitGO = new GameObject();
  Text* textQuit = new Text(
    *textQuitGO,
    DEFAULT_FONT_PATH,
    DEFAULT_FONT_SIZE,
    Text::TextStyle::SOLID,
    END_QUIT_MESSAGE,
    WHITE
  );
  textQuitGO->box.x = 50;
  textQuitGO->box.y = 50;
  textQuitGO->AddComponent(textQuit);
  textQuit->SetCameraFollower(true);
  AddObject(textQuitGO);

  GameObject* textMessageGO = new GameObject();
  Text* textMessage = new Text(
    *textMessageGO,
    DEFAULT_FONT_PATH,
    DEFAULT_FONT_SIZE,
    Text::TextStyle::SOLID,
    END_MESSAGE,
    WHITE,
    BLACK,
    true,
    END_BLINK_SHOW_TIME,
    END_BLINK_HIDDEN_TIME
  );
  textMessageGO->box.SetCenter({DEFAULT_SCREEN_WIDTH / 2, DEFAULT_SCREEN_HEIGHT / 2});
  textMessage->SetCameraFollower(true);
  textMessageGO->AddComponent(textMessage);
  AddObject(textMessageGO);
}

void EndState::Start() {
  if (!started) {
    LoadAssets();
    
    StartArray();
    std::cout << "EndState started!\n";

    backgroundMusic.Play();

    started = true;
  }
}

void EndState::Update(float dt) {
  UpdateArray(dt);

  InputManager& input = InputManager::GetInstance();

  if (input.QuitRequested() || input.KeyPress(ESCAPE_KEY)) {
    quitRequested = true;
  }

  if (input.KeyPress(SPACE_BAR)) {
    popRequested = true;
  }
}

void EndState::Render() {
  RenderArray();
}

void EndState::Pause() {
  backgroundMusic.Stop();
}

void EndState::Resume() {
  backgroundMusic.Play();
}
