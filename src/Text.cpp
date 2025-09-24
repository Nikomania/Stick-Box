#include <Text.h>
#include <Resources.h>
#include <Game.h>
#include <Camera.h>

Text::Text(
  GameObject& associated,
  std::string fontFile,
  int fontSize,
  TextStyle style,
  std::string text,
  SDL_Color color,
  SDL_Color color_bg,
  bool blinking,
  float showTime,
  float hiddenTime
) : Component(associated),
font(nullptr),
texture(nullptr),
text(text),
style(style),
fontFile(fontFile),
fontSize(fontSize),
color(color),
color_bg(color_bg),
cameraFollower(false),
blinking(blinking),
showTime(showTime),
hiddenTime(hiddenTime),
timerBlinking(),
isShowing(true) {
  font = Resources::GetFont(fontFile, fontSize);
  RemakeTexture();
}

Text::~Text() {}

void Text::Update(float dt) {
  timerBlinking.Update(dt);

  if (blinking) {
    if (isShowing) {
      if (timerBlinking.Get() > showTime) {
        isShowing = false;
        timerBlinking.Restart();
      }
    } else {
      if (timerBlinking.Get() > hiddenTime) {
        isShowing = true;
        timerBlinking.Restart();
      }
    }
  }
}

void Text::Render() {
  if (!isShowing) {
    return;
  }

  if (texture != nullptr) {
    SDL_Rect clipRect;
    clipRect.x = 0;
    clipRect.y = 0;
    clipRect.w = associated.box.w;
    clipRect.h = associated.box.h;

    SDL_Rect dstRect;
    dstRect.x = associated.box.x + (cameraFollower ? 0 : -1) * Camera::pos.x;
    dstRect.y = associated.box.y + (cameraFollower ? 0 : -1) * Camera::pos.y;
    dstRect.w = clipRect.w;
    dstRect.h = clipRect.h;

    SDL_RenderCopyEx(
      Game::GetInstance().GetRenderer(),
      texture,
      &clipRect,
      &dstRect,
      associated.angleDeg,
      nullptr,
      SDL_FLIP_NONE
    );
  }
}

bool Text::Is(std::string type) {
  return type == "Text";
}

void Text::Start() {
  timerBlinking.Restart();
}

void Text::SetText(std::string text) {
  this->text = text;
  RemakeTexture();
}

void Text::SetCameraFollower(bool cameraFollower) {
  this->cameraFollower = cameraFollower;
}

void Text::SetColor(SDL_Color color) {
  this->color = color;
  RemakeTexture();
}

void Text::SetBackgroundColor(SDL_Color color_bg) {
  this->color_bg = color_bg;
  RemakeTexture();
}

void Text::SetStyle(TextStyle style) {
  this->style = style;
  RemakeTexture();
}

void Text::SetFontFile(std::string fontFile) {
  this->fontFile = fontFile;
  font = Resources::GetFont(fontFile, fontSize);
  RemakeTexture();
}

void Text::SetFontSize(int fontSize) {
  this->fontSize = fontSize;
  font = Resources::GetFont(fontFile, fontSize);
  RemakeTexture();
}

void Text::RemakeTexture() {
  if (texture != nullptr) {
    SDL_DestroyTexture(texture);
  }

  SDL_Surface* surface = nullptr;

  switch (style) {
    case TextStyle::SOLID:
      surface = TTF_RenderText_Solid(font.get(), text.c_str(), color);
      break;
    case TextStyle::SHADED:
      surface = TTF_RenderText_Shaded(font.get(), text.c_str(), color, color_bg);
      break;
    case TextStyle::BLENDED:
      surface = TTF_RenderText_Blended(font.get(), text.c_str(), color);
      break;
    default:
      throw std::runtime_error("Invalid TextStyle!");
      break;
  }

  if (surface == nullptr) {
    throw std::runtime_error("Failed to create text surface!");
  }

  texture = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), surface);
  SDL_FreeSurface(surface);

  if (texture == nullptr) {
    throw std::runtime_error("Failed to create text texture!");
  }

  int w, h;
  SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
  associated.box.w = w;
  associated.box.h = h;
}