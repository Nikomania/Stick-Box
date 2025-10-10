#include <State/CloseCombatState.h>
#include <Resource/Music.h>
#include <Core/GameObject.h>
#include <Manager/SpriteRenderer.h>
#include <Level/TileSet.h>
#include <Level/TileMap.h>
#include <Manager/InputManager.h>
#include <HUD/Camera.h>
#include <Entity/Character.h>
#include <Controller/PlayerController.h>
#include <Physics/Collision.h>
#include <Physics/Collider.h>
#include <DataStructure/GameData.h>
#include <State/EndState.h>
#include <Core/Game.h>
#include <DataStructure/constants.h>
#include <Level/Platform.h>

CloseCombatState::CloseCombatState(exit_t playerEntrance) :
LevelState(playerEntrance),
backgroundMusic(),
tileSet(nullptr) {
  sortY = true;
  SDL_Log("CloseCombatState created!\n");
}

void CloseCombatState::LoadAssets() {
  GameObject* bgGO = new GameObject();
  bgGO->box.x = BG_DEFAULT_POS;
  bgGO->box.y = BG_DEFAULT_POS;
  SpriteRenderer* bgSprite = new SpriteRenderer(*bgGO, BG_PATH, 1, 1);
  bgSprite->SetCameraFollower(true);
  bgGO->AddComponent(bgSprite);
  AddObject(bgGO);
  backgroundElements++;

  GameObject* tileMapGO = new GameObject();
  tileMapGO->box.x = 0;
  tileMapGO->box.y = 0;
  tileSet = new TileSet(TILE_SET_FRAME_WIDTH, TILE_SET_FRAME_HEIGHT, TILE_SET_PATH);
  TileMap *tileMap = new TileMap(*tileMapGO, TILE_MAP_PATH, tileSet);
  tileMapGO->AddComponent(tileMap);
  AddObject(tileMapGO);
  backgroundElements++;

  GameObject* characterGO = new GameObject();
  characterGO->box.x = CHARACTER_INIT_X;
  characterGO->box.y = CHARACTER_INIT_Y;
  Character* character = new Character(*characterGO, CHARACTER_PATH, CHARACTER_HP);
  Character::player = character;
  characterGO->AddComponent(character);
  characterGO->AddComponent(new PlayerController(*characterGO));
  Camera::Follow(characterGO);
  AddObject(characterGO);

  GameObject* platformGO = new GameObject();
  platformGO->box.x = 1000;
  platformGO->box.y = 1400;
  platformGO->box.w = 300;
  platformGO->box.h = 50;
  platformGO->AddComponent(new Platform(*platformGO));
  AddObject(platformGO);

  backgroundMusic.Open(MUSIC_PATH);
  SDL_Log("Music loaded!\n");

  SDL_Log("Assets loaded!\n");
}

void CloseCombatState::Start() {
  if (!started) {
    LoadAssets();

    StartArray();
    std::cout << "CloseCombatState started!\n";

    backgroundMusic.Play();

    started = true;
  }
}

void CloseCombatState::Update(float dt) {
  UpdateArray(dt);

  Camera::Update(dt);

  const int size = objectArray.size();
  for (int i = size - 1; i >= 0; i--) {
    if ((*(objectArray.begin() + i))->IsDead()) {
      objectArray.erase((objectArray.begin() + i));
    }
  }

  InputManager& input = InputManager::GetInstance();

  if (input.KeyPress(B_KEY)) {
    if (Mix_PlayingMusic()) {
      backgroundMusic.Stop();
    } else {
      backgroundMusic.Play();
    }
  }

  if (input.QuitRequested() || input.KeyPress(ESCAPE_KEY)) {
    popRequested = true;
  }

  if (input.KeyPress(G_KEY)) {
    Character::player->godMode = !Character::player->godMode;
  }

  const int size2 = objectArray.size();
  for (int i = 0; i < size2; i++) {
    if (objectArray[i]->GetComponent("Collider")) {
      Collider* collider = static_cast<Collider*>(objectArray[i]->GetComponent("Collider"));
      for (int j = i + 1; j < size2; j++) {
        if (objectArray[j]->GetComponent("Collider")) {
          Collider* otherCollider = static_cast<Collider*>(objectArray[j]->GetComponent("Collider"));
          Vec2* MTV = Collision::GetMTV(
            collider->box, otherCollider->box,
            objectArray[i]->angleDeg * M_PI / 180,
            objectArray[j]->angleDeg * M_PI / 180
          );
          if (
            MTV != nullptr
          ) {
            objectArray[i]->NotifyCollision(*objectArray[j], *MTV);
            objectArray[j]->NotifyCollision(*objectArray[i], (*MTV) * -1);

            delete MTV;
          }
        }
      }
    }
  }
}

void CloseCombatState::Render() {
  RenderArray();
}

void CloseCombatState::Pause() {
  backgroundMusic.Stop();
}

void CloseCombatState::Resume() {
  backgroundMusic.Play();
}
