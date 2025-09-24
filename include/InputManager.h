#pragma once

#include <unordered_map> 
#include <SDL2/SDL.h>

#define LEFT_ARROW_KEY SDLK_LEFT
#define RIGHT_ARROW_KEY SDLK_RIGHT
#define UP_ARROW_KEY SDLK_UP
#define DOWN_ARROW_KEY SDLK_DOWN
#define ESCAPE_KEY SDLK_ESCAPE
#define LEFT_MOUSE_BUTTON SDL_BUTTON_LEFT
#define RIGHT_MOUSE_BUTTON SDL_BUTTON_RIGHT
#define SPACE_BAR SDLK_SPACE

#define D_KEY SDLK_d
#define A_KEY SDLK_a
#define W_KEY SDLK_w
#define S_KEY SDLK_s
#define R_KEY SDLK_r
#define I_KEY SDLK_i
#define B_KEY SDLK_b
#define L_KEY SDLK_l
#define F_KEY SDLK_f
#define K_KEY SDLK_k
#define P_KEY SDLK_p
#define G_KEY SDLK_g

class InputManager {
private:
  bool mouseState[6];
  int mouseUpdate[6];

  std::unordered_map<int, bool> keyState;
  std::unordered_map<int, int> keyUpdate;

  bool quitRequested;

  int updateCounter;

  int mouseX;
  int mouseY;

  InputManager();
  ~InputManager();
public:
  void Update();

  bool KeyPress(int key);
  bool KeyRelease(int key);
  bool IsKeyDown(int key);

  bool MousePress(int button);
  bool MouseRelease(int button);
  bool IsMouseDown(int button);

  int GetMouseX();
  int GetMouseY();

  bool QuitRequested();

  static InputManager& GetInstance();
};
