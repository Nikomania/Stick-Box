#pragma once

#include <SDL2/SDL_ttf.h>
#include <DataStructure/Component.h>
#include <Utils/Timer.h>
#include <string>
#include <memory>

const SDL_Color WHITE = {255, 255, 255, 255};
const SDL_Color BLACK = {0, 0, 0, 255};
const SDL_Color RED = {255, 0, 0, 255};
const SDL_Color GREEN = {0, 255, 0, 255};
const SDL_Color BLUE = {0, 0, 255, 255};
const SDL_Color YELLOW = {255, 255, 0, 255};
const SDL_Color CYAN = {0, 255, 255, 255};
const SDL_Color MAGENTA = {255, 0, 255, 255};
const SDL_Color ORANGE = {255, 165, 0, 255};
const SDL_Color PURPLE = {128, 0, 128, 255};
const SDL_Color PINK = {255, 192, 203, 255};
const SDL_Color BROWN = {165, 42, 42, 255};
const SDL_Color GRAY = {128, 128, 128, 255};

class Text : public Component {
public:
  enum TextStyle { SOLID, SHADED, BLENDED };

  Text(
    GameObject& associated,
    std::string fontFile,
    int fontSize,
    TextStyle style,
    std::string text,
    SDL_Color color,
    SDL_Color color_bg=BLACK,
    bool blinking=false,
    float showTime=0,
    float hiddenTime=0
  );
  ~Text() override;

  void Update(float dt) override;
  void Render() override;
  bool Is(std::string type) override;
  void Start() override;

  void SetText(std::string text);
  void SetCameraFollower(bool cameraFollower);
  void SetColor(SDL_Color color);
  void SetBackgroundColor(SDL_Color color_bg);
  void SetStyle(TextStyle style);
  void SetFontFile(std::string fontFile);
  void SetFontSize(int fontSize);
private:
  void RemakeTexture();

  std::shared_ptr<TTF_Font> font;
  SDL_Texture* texture;
  std::string text;
  TextStyle style;
  std::string fontFile;
  int fontSize;
  SDL_Color color;
  SDL_Color color_bg;

  bool cameraFollower;

  bool blinking;
  bool isShowing;
  float showTime;
  float hiddenTime;
  Timer timerBlinking;
};
