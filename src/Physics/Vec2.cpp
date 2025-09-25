#include <Physics/Vec2.h>
#include <cmath>

Vec2::Vec2() {
  x = 0;
  y = 0;
}

Vec2::Vec2(float x, float y) {
  this->x = x;
  this->y = y;
}

Vec2::Vec2(const Vec2& other) {
  x = other.x;
  y = other.y;
}

Vec2 Vec2::operator+(const Vec2& other) const {
  return Vec2(x + other.x, y + other.y);
}

Vec2 Vec2::operator-(const Vec2& other) const {
  return Vec2(x - other.x, y - other.y);
}

Vec2 Vec2::operator*(float scalar) const {
  return Vec2(x * scalar, y * scalar);
}

Vec2 Vec2::operator/(float scalar) const {
  return Vec2(x / scalar, y / scalar);
}

bool Vec2::operator==(const Vec2& other) const {
  return x == other.x && y == other.y;
}

Vec2 Vec2::operator+=(const Vec2& other) {
  *this = *this + other;
  return *this;
}

float Vec2::Magnitude() const {
  return sqrt(x * x + y * y);
}

float Vec2::HorAngle() const {
  return atan2(y, x);
}

Vec2 Vec2::Normalize() const {
  const float mag = Magnitude();
  return (mag > 0 ? operator/(mag) : Vec2());
}

Vec2 Vec2::Rotate(float angle) const {
  return Vec2(x * cos(angle) - y * sin(angle), x * sin(angle) + y * cos(angle));
}

float Vec2::Distance(const Vec2& other) const {
  return (other - *this).Magnitude();
}

float Vec2::Angle(const Vec2& other) const {
  return acos(Dot(other) / (Magnitude() * other.Magnitude()));
}

float Vec2::Slope(const Vec2& other) const {
  return (other.y - y) / (other.x - x);

}
float Vec2::Dot(const Vec2& other) const {
  return x * other.x + y * other.y;
}
