#include <DataStructure/State.h>
#include <SDL2/SDL.h>

State::State() :
popRequested(false),
quitRequested(false),
started(false),
sortY(false),
backgroundElements(0),
objectArray() {
  SDL_Log("State created!\n");
}

State::~State() {
  objectArray.clear();
}

std::weak_ptr<GameObject> State::AddObject(GameObject* go) {
  std::shared_ptr<GameObject> goPtr(go);
  objectArray.emplace_back(goPtr);
  if (started) {
    goPtr->Start();
  }
  std::weak_ptr<GameObject> weakObject = goPtr;
  return weakObject;
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject* go) {
  const int size = objectArray.size();
  for (int i = 0; i < size; i++) {
    if (objectArray[i].get() == go) {
      std::weak_ptr<GameObject> weakObject = objectArray[i];
      return weakObject;
    }
  }
  return std::weak_ptr<GameObject>();
}

bool State::PopRequested() {
  return popRequested;
}

bool State::QuitRequested() {
  return quitRequested;
}

void State::StartArray() {
  const int size = objectArray.size();
  for (int i = 0; i < size; i++) {
    objectArray[i]->Start();
  }
}

void State::UpdateArray(float dt) {
  const int size = objectArray.size();
  for (int i = 0; i < size; i++) {
    objectArray[i]->Update(dt);
  }
}

void State::RenderArray() {
  const int size = objectArray.size();
  std::vector<std::shared_ptr<GameObject>> render_vector;
  if (sortY) {
    for (int i = 0; i < size; i++) {
      render_vector.emplace_back(objectArray[i]);
    }
    qsort(
      &render_vector[backgroundElements],
      render_vector.size() - backgroundElements,
      sizeof(std::shared_ptr<GameObject>),
      GameObject::Compare
    );
  } else {
    render_vector = objectArray;
  }

  for (int i = 0; i < size; i++) {
    render_vector[i]->Render();
  }
}
