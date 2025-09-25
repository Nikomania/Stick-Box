#include <Physics/Rect.h>
#include <Physics/Vec2.h>
#include <cmath>

Rect::Rect() {
  x = 0;
  y = 0;
  w = 0;
  h = 0;
}

Rect::Rect(float x, float y, float width, float height) {
  this->x = x;
  this->y = y;
  w = width;
  h = height;
}

Rect::Rect(const Vec2& pos, float width, float height) {
  x = pos.x;
  y = pos.y;
  w = width;
  h = height;
}

Rect::Rect(const Vec2& beg, const Vec2& end) {
  x = beg.x;
  y = beg.y;
  w = end.x - beg.x;
  h = end.y - beg.y;
}

Rect::Rect(const Rect& other) {
  x = other.x;
  y = other.y;
  w = other.w;
  h = other.h;
}

float Rect::GetArea() const {
  return w * h;
}

float Rect::GetPerimeter() const {
  return 2 * (w + h);
}

Vec2 Rect::GetCenter() const {
  return Vec2(x + w / 2, y + h / 2);
}

Vec2 Rect::GetPos() const {
  return Vec2(x, y);
}

float Rect::GetDiagonal() const {
  return sqrt(w * w + h * h);
}

float Rect::GetDistanceCenters(const Rect& other) const {
  return GetCenter().Distance(other.GetCenter());
}

Rect Rect::operator+(const Vec2& vec) const {
  return Rect(x + vec.x, y + vec.y, w, h);
}

Rect Rect::operator-(const Vec2& vec) const {
  return Rect(x - vec.x, y - vec.y, w, h);
}

Rect Rect::operator*(float scalar) const {
  return Rect(x * scalar, y * scalar, w * scalar, h * scalar);
}

Rect Rect::operator/(float scalar) const {
  return Rect(x / scalar, y / scalar, w / scalar, h / scalar);
}

Rect& Rect::Move(const Vec2& speedVec) {
  x += speedVec.x;
  y += speedVec.y;
  return *this;
}

Vec2 Rect::Move(float angle, float speed) {
  Vec2 speedVec = Vec2(speed, 0).Rotate(angle);
  Move(speedVec);
  return speedVec;
}

Rect& Rect::SetPos(const Vec2& pos) {
  x = pos.x;
  y = pos.y;
  return *this;
}

Rect& Rect::SetCenter(const Vec2& pos) {
  x = pos.x - w / 2;
  y = pos.y - h / 2;
  return *this;
}

bool Rect::Contains(const Vec2& point) const {
  return point.x >= x && point.x <= x + w && point.y >= y && point.y <= y + h;
}

bool Rect::Contains(float x, float y) const {
  return x >= this->x && x <= this->x + w && y >= this->y && y <= this->y + h;
}
