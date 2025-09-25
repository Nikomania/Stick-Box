#include <Manager/InputManager.h>
#include <SDL2/SDL.h>

InputManager& InputManager::GetInstance() {
  static InputManager instance;
  return instance;
}

InputManager::InputManager() {
  for (int i = 0; i < 6; i++) {
    mouseState[i] = false;
    mouseUpdate[i] = 0;
  }

  quitRequested = false;
  updateCounter = 0;
  mouseX = 0;
  mouseY = 0;
}

void InputManager::Update() {
  SDL_Event event;
  quitRequested = false;
  updateCounter++;

  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      quitRequested = true;
    }

    if (event.type == SDL_MOUSEBUTTONDOWN && event.key.repeat == 0) {
      mouseState[event.button.button] = true;
      mouseUpdate[event.button.button] = updateCounter;
    }

    if (event.type == SDL_MOUSEBUTTONUP) {
      mouseState[event.button.button] = false;
      mouseUpdate[event.button.button] = updateCounter;
    }

    if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
      keyState[event.key.keysym.sym] = true;
      keyUpdate[event.key.keysym.sym] = updateCounter;
    }

    if (event.type == SDL_KEYUP) {
      keyState[event.key.keysym.sym] = false;
      keyUpdate[event.key.keysym.sym] = updateCounter;
    }
  }

  SDL_GetMouseState(&mouseX, &mouseY);
}

bool InputManager::KeyPress(int key) {
  return keyState[key] && keyUpdate[key] == updateCounter;
}

bool InputManager::KeyRelease(int key) {
  return !keyState[key] && keyUpdate[key] == updateCounter;
}

bool InputManager::IsKeyDown(int key) {
  return keyState[key];
}

bool InputManager::MousePress(int button) {
  return mouseState[button] && mouseUpdate[button] == updateCounter;
}

bool InputManager::MouseRelease(int button) {
  return !mouseState[button] && mouseUpdate[button] == updateCounter;
}

bool InputManager::IsMouseDown(int button) {
  return mouseState[button];
}

int InputManager::GetMouseX() {
  return mouseX;
}

int InputManager::GetMouseY() {
  return mouseY;
}

bool InputManager::QuitRequested() {
  return quitRequested;
}

InputManager::~InputManager() {

}
